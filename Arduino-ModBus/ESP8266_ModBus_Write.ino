#ifdef ESP8266
 #include <ESP8266WiFi.h>
#else
 #include <WiFi.h>
#endif

// https://github.com/emelianov/modbus-esp8266
#include <ModbusIP_ESP8266.h>

const int REG_V40p0 = 320;               // Modbus Coil Offset
const int REG_V40p1 = 321;               // Modbus Coil Offset
const int REG_VW42  = 21;                // Modbus Hreg Offset

IPAddress remote(192, 168, 1, 100);  // Address of Modbus Slave device
const int port = 502;
const int LOOP_COUNT = 30;

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

uint8_t show = LOOP_COUNT;

uint8_t setToOn = 1;

void loop() {
  if (mb.isConnected(remote)) {   // Check if connection to Modbus Slave is established

    if (show == LOOP_COUNT) {
      if (setToOn == 1) {
        Serial.println("Set M5 to: 1 (V40.0)");
        mb.writeCoil(remote, REG_V40p0, true);    // Initiate Write Coil to Modbus Slave
        mb.writeCoil(remote, REG_V40p0, false);   // Initiate Write Coil to Modbus Slave
        setToOn = 0;
      } else {
        Serial.println("Set M5 to: 0 (V40.1)");
        mb.writeCoil(remote, REG_V40p1, true);    // Initiate Write Coil to Modbus Slave
        mb.writeCoil(remote, REG_V40p1, false);   // Initiate Write Coil to Modbus Slave
        setToOn = 1;
      }
    }

    mb.writeHreg(remote, REG_VW42, show);  // Initiate Write Hreg to Modbus Slave
    
  } else {
    mb.connect(remote, port);           // Try to connect if no connection
  }
  mb.task();                      // Common local Modbus task
  delay(100);                     // Pulling interval
  if (!show--) {

    show = LOOP_COUNT;
  }
}
