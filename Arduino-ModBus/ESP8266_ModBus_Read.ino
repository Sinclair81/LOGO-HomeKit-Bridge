#ifdef ESP8266
 #include <ESP8266WiFi.h>
#else
 #include <WiFi.h>
#endif

// https://github.com/emelianov/modbus-esp8266
#include <ModbusIP_ESP8266.h>

const int REG_AM2 = 529;                 // Modbus Hreg Offset
const int REG_AM9 = 536;                 // Modbus Hreg Offset
const int REG_M5 = 8260;                 // Modbus Coil Offset

IPAddress remote(192, 168, 1, 100);  // Address of Modbus Slave device
const int port = 502;
const int LOOP_COUNT = 10;

ModbusIP mb;  //ModbusIP object

void setup() {
  Serial.begin(115200);
 
  WiFi.begin("SSID", "PWD");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  mb.client();
}

uint16_t res_am2 = 0;
uint16_t res_am9 = 0;
bool     res_m5  = false;
uint8_t show = LOOP_COUNT;

void loop() {
  if (mb.isConnected(remote)) {   // Check if connection to Modbus Slave is established
    mb.readHreg(remote, REG_AM2, &res_am2);  // Initiate Read Hreg from Modbus Slave
    mb.readHreg(remote, REG_AM9, &res_am9);  // Initiate Read Hreg from Modbus Slave
    mb.readCoil(remote, REG_M5,  &res_m5);   // Initiate Read Coil from Modbus Slave
  } else {
    mb.connect(remote, port);           // Try to connect if no connection
  }
  mb.task();                      // Common local Modbus task
  delay(100);                     // Pulling interval
  if (!show--) {                  // Display Slave register value one time per second (with default settings)
    Serial.print("AM2: "); Serial.println(res_am2);
    Serial.print("AM9: "); Serial.println(res_am9);
    Serial.print("M5:  "); Serial.println(res_m5);
    show = LOOP_COUNT;
  }
}
