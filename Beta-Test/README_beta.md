# [Beta Test] LOGO-HomeKit-Bridge [Beta Test] #

[![donate](https://img.shields.io/badge/donate-PayPal-blue.svg)](https://www.paypal.me/Sinclair81)

<!-- markdownlint-disable MD033 -->
<img src="https://raw.githubusercontent.com/Sinclair81/Logo-HomeKit-Bridge/master/Images/Bridge-FS2e.jpg" align="right" alt="Bridge" height="289" width="400">
<!-- markdownlint-enable MD033 -->

A HomeKit Bridge for Siemens LOGO!s.  

__Requires components:__

- ESP32-S2 board  
- Ethernet interface with WIZnet W5500  
- SD card adapter  
- Mac or PC with EspTool installed

__Example configuration:__

- [FeatherS2](https://feathers2.io/)
- [MKR ETH Shield](https://store.arduino.cc/arduino-mkr-eth-shield)  
- my PCB  

__Infos:__  
  
- The connection on the underside of the MKR ETH Shield from the ETH_INT pad to pin 3 must be made by yourself! Without it, the Ethernet connection will not work!  
- The mac address is the ethernet mac address from the ESP32-S2 chip and not that from the sticker on the shield.  
- HomeKit configuration code is 111-22-333.  
- In the serial connection you can see the HomeKit configuration QR code. And lots of other useful information and error messages.

__Future options and ideas:__  

- modify the PCB to add a 24V input and DIN rail support `@acresp`
- access to bridge.cfg "over the air" to add/remove accessory without removing the SD card `@acresp`
- Alexa support.
  
__Type of Accessory:__

- [Switch](#switch-configuration)  
- [Lightbulb](#lightbulb-configuration)  
- [Blind](#blind-configuration)  
- [Window](#window-configuration)  
- [Garage Door](#garage-door-configuration)  
- [Thermostat](#thermostat-configuration)
- [Irrigation System](#irrigation-system-configuration)
- [Valve](#valve-configuration)
- [Fan](#fan-configuration)
- [Filter Maintenance](#filter-maintenance-configuration)
  
__Flash:__  

`$ esptool.py -p [USB_device] -b 460800 --before=no_reset --after=no_reset write_flash --flash_mode dio --flash_freq 80m --flash_size 16MB 0x1000 bootloader.bin 0x20000 ethernet_bridge.bin 0x8000 partition-table.bin 0x16000 ota_data_initial.bin`  
  
## LOGO-HomeKit-Bridge Main Configuration Parameters ##  
  
Name                     | Value               | Required | Notes  
------------------------ | ------------------- | -------- | ------------------------  
`port`                   | 502                 | yes      | Must be set to the Modbus Port of your LOGO! PLCs.  
`plcs`                   | [...]               | yes      | A array of all your LOGO! PLCs.  
  
## PLC Configuration ##  
  
Name                     | Value               | Required | Notes  
------------------------ | ------------------- | -------- | ------------------------  
`name`                   | "Logo 1"            | yes      | Name of your LOGO! PLC.  
`ip`                     | "192.168.1.100"     | yes      | Must be set to the IP of your LOGO! PLC.  
`items`                  | [...]               | yes      | A array of all accessorys and or sensors from this LOGO! PLC.  
  
## Main Item Configuration ##  
  
Name                     | Value               | Required | Option for  | Notes  
------------------------ | ------------------- | -------- | ----------- | ------------------------  
`name`                   | (custom)            | yes      | all         | Name of accessory that will appear in homekit app.
`type`                   | "switch" or ...     | yes      | all         | Type of Accessory or Sensor
`pushButton`             | 0 or 1              | no       | all         | If e.g. the network input in the LOGO! a hardware button on the LOGO! simulated, default is: 1.  
  
## Switch Configuration ##  
  
Name                     | Value               | Required | Option for | Notes  
------------------------ | ------------------- | -------- | ---------- | ------------------------  
`switchGet`              | "Q1"                | yes*     | "switch"   | Switch Get - Qn, Mn or Vn.n  
`switchSetOn`            | "V1.0"              | yes*     | "switch"   | Switch Set On - Mn or Vn.n  
`switchSetOff`           | "V1.1"              | yes*     | "switch"   | Switch Set Off - Mn or Vn.n  

```json
{
    "name": "Item-1",
    "type": "switch",
    "switchGet": "Q1",
    "switchSetOn": "V1.0",
    "switchSetOff": "V1.1"
}
```  
  
## Lightbulb Configuration ##  
  
Name                     | Value               | Required | Option for | Notes  
------------------------ | ------------------- | -------- | ---------- | ------------------------  
`lightbulbGet`           | "Q4"                | yes*     | "lightbulb" | Lightbulb Get - Qn, Mn or Vn.n  
`lightbulbSetOn`         | "V2.0"              | yes*     | "lightbulb" | Lightbulb Set On - Mn or Vn.n
`lightbulbSetOff`        | "V2.1"              | yes*     | "lightbulb" | Lightbulb Set Off - Mn or Vn.n
`lightbulbSetBrightness` | "VW20"              | no*      | "lightbulb" | Lightbulb Set Brightness - AMn or VWn
`lightbulbGetBrightness` | "VW22"              | no*      | "lightbulb" | Lightbulb Get Brightness - AMn or VWn

```json
{
    "name": "Item-5",
    "type": "lightbulb",
    "lightbulbGet": "Q4",
    "lightbulbSetOn": "V2.0",
    "lightbulbSetOff": "V2.1",
    "lightbulbSetBrightness": "VW20",
    "lightbulbGetBrightness": "VW22"
}
```  

## Blind Configuration ##
  
Name                     | Value               | Required | Option for | Notes
------------------------ | ------------------- | -------- | ---------- | ------------------------
`blindSetTargetPos`      | "VW26"              | yes*     | "blind"    | Blind Set Target Pos - AMn or VWn
`blindGetTargetPos`      | "VW26"              | yes*     | "blind"    | Blind Get Target Pos - AMn or VWn
`blindGetPos`            | "VW28"              | yes*     | "blind"    | Blind Get Pos - AMn or VWn
`blindGetState`          | "VW30"              | yes*     | "blind"    | Blind Get State - AMn or VWn
`blindConvertValue`      | 0 or 1              | no*      | "blind"    | Convert LOGO! values in to HomeKit values, default is: 1.  
  
```json
{
    "name": "Item-6",
    "type": "blind",
    "blindConvertValue": 1,
    "blindSetTargetPos": "VW26",
    "blindGetTargetPos": "VW26",
    "blindGetPos": "VW28",
    "blindGetState": "VW30"
}
```  

## Window Configuration ##
  
Name                     | Value               | Required | Option for | Notes
------------------------ | ------------------- | -------- | ---------- | ------------------------
`windowSetTargetPos`     | "VW32"              | yes*     | "window"   | Window Set Target Pos - AMn or VWn
`windowGetTargetPos`     | "VW32"              | yes*     | "window"   | Window Get Target Pos - AMn or VWn
`windowGetPos`           | "VW34"              | yes*     | "window"   | Window Get Pos - AMn or VWn
`windowSetState`         | "VW36"              | yes*     | "window"   | Window Get State - AMn or VWn
`windowConvertValue`     | 0 or 1              | no*      | "window"   | Convert LOGO! values in to HomeKit values, default is: 1.  
  
```json
{
    "name": "Item-7",
    "type": "window",
    "windowConvertValue": 1,
    "windowSetTargetPos": "VW32",
    "windowGetTargetPos": "VW32",
    "windowGetPos": "VW34",
    "windowGetState": "VW36"
}
```  

## Garage Door Configuration ##

Name                       | Value               | Required | Option for   | Notes
-------------------------- | ------------------- | -------- | ------------ | ------------------------
`garagedoorGetState`       | "VW40"              | yes*     | "garagedoor" | Garagedoor Get State - AMn or VWn (0 = Open; 1 = Closed; 2 = Opening; 3 = Closing; 4 = Stopped)
`garagedoorGetTargetState` | "VW40"              | yes*     | "garagedoor" | Garagedoor Get Target State - AMn or VWn (0 = Open; 1 = Closed)
`garagedoorSetTargetState` | "VW38"              | yes*     | "garagedoor" | Garagedoor Set Target State - AMn or VWn (0 = Open; 1 = Closed)
`garagedoorObstruction`    | "V3.0"              | no*      | "garagedoor" | Garagedoor Obstruction Detected - Mn or Vn.n

```json
{
    "name": "Item-8",
    "type": "garagedoor",
    "garagedoorGetState": "VW40",
    "garagedoorGetTargetState": "VW40",
    "garagedoorSetTargetState": "VW38",
    "garagedoorObstruction": "V3.0"
}
```

## Thermostat Configuration ##

Name                     | Value              | Required | Option for | Notes
------------------------ | ------------------ | -------- | ---------- | ------------------------
`thermostatGetHCState`       | "VW42"         | yes*     | "thermostat" | Thermostat Get Heating Cooling State - AMn or VWn
`thermostatGetTargetHCState` | "VW44"         | yes*     | "thermostat" | Thermostat Get Target Heating Cooling State - AMn or VWn
`thermostatSetTargetHCState` | "VW46"         | yes*     | "thermostat" | Thermostat Set Target Heating Cooling State - AMn or VWn
`thermostatGetTemp`          | "VW48"         | yes*     | "thermostat" | Thermostat Get Temperature - AMn or VWn - Current Temperature in °C (0°C - 100°C!!, a value of 105 is 10.5°C)
`thermostatGetTargetTemp`    | "VW50"         | yes*     | "thermostat" | Thermostat Get Target Temperature - AMn or VWn - Current Temperature in °C (10°C - 38°C!!, a value of 105 is 10.5°C)
`thermostatSetTargetTemp`    | "VW52"         | yes*     | "thermostat" | Thermostat Set Target Temperature - AMn or VWn
`thermostatTempDisplayUnits` | 0              | yes*     | "thermostat" | Temperature Display Units - Celsius = 0; Fahrenheit = 1;

```json
{
    "name": "Item-9",
    "type": "thermostat",
    "thermostatGetHCState": "VW42",
    "thermostatGetTargetHCState": "VW44",
    "thermostatSetTargetHCState": "VW46",
    "thermostatGetTemp": "VW48",
    "thermostatGetTargetTemp": "VW50",
    "thermostatSetTargetTemp": "VW52",
    "thermostatTempDisplayUnits": 0
}
```

## Irrigation System Configuration ##

Name                     | Value               | Required | Option for | Notes
------------------------ | ------------------- | -------- | ---------- | ------------------------
`irrigationSystemGetActive`      | "V4.0"    | yes*     | "irrigationSystem" | Irrigation System Get Active - Mn or Vn.n
`irrigationSystemSetActiveOn`    | "V4.1"    | yes*     | "irrigationSystem" | Irrigation System Set Active to On - Mn or Vn.n
`irrigationSystemSetActiveOff`   | "V4.2"    | yes*     | "irrigationSystem" | Irrigation System Set Active to Off - Mn or Vn.n
`irrigationSystemGetProgramMode` | "VW54"     | yes*     | "irrigationSystem" | Irrigation System Get Program Mode - AMn or VWn - (0 - No Program scheduled; 1 - Program scheduled; 2 - Program scheduled manual Mode)
`irrigationSystemGetInUse`       | "V4.3"    | yes*     | "irrigationSystem" | Irrigation System Get In Use - Mn or Vn.n

```json
{
    "name": "Item-10",
    "type": "irrigationSystem",
    "irrigationSystemGetActive": "V4.0",
    "irrigationSystemSetActiveOn": "V4.1",
    "irrigationSystemSetActiveOff": "V4.2",
    "irrigationSystemGetProgramMode": "VW54",
    "irrigationSystemGetInUse": "V4.3"
}
```

## Valve Configuration ##

Name                        | Value       | Required | Option for | Notes
--------------------------- | ----------- | -------- | ---------- | ------------------------
`valveGetActive`            | "V5.0"      | yes*     | "valve" | Valve Get Active - Mn or Vn.n
`valveSetActiveOn`          | "V5.1"      | yes*     | "valve" | Valve Set Active to On - Mn or Vn.n
`valveSetActiveOff`         | "V5.2"      | yes*     | "valve" | Valve Set Active to Off - Mn or Vn.n
`valveGetInUse`             | "V5.3"      | yes*     | "valve" | Valve Get In Use - Mn or Vn.n
`valveType`                 | 0           | yes*     | "valve" | Valve Type - Generic Valve = 0, Irrigation = 1, Shower Head = 2, Water Faucet = 3,
`valveSetDuration`          | "VW56"      | no*      | "valve" | Valve Set Duration - AMn or VWn - Value in Seconds (0 - 3600 sec)
`valveGetDuration`          | "VW56"      | no*      | "valve" | Valve Get Duration - AMn or VWn - Value in Seconds (0 - 3600 sec)
`valveGetRemainingDuration` | "VW58"      | no*      | "valve" | Valve Get Remaining Duration - AMn or VWn - Value in Seconds (0 - 3600 sec)

```json
{
    "name": "Item-11",
    "type": "valve",
    "valveGetActive": "V5.0",
    "valveSetActiveOn": "V5.1",
    "valveSetActiveOff": "V5.2",
    "valveGetInUse": "V5.3",
    "valveType": 1,
    "valveSetDuration": "VW56",
    "valveGetDuration": "VW56",
    "valveGetRemainingDuration": "VW58"
}
```

## Fan Configuration ##

Name                     | Value             | Required | Option for | Notes
------------------------ | ----------------- | -------- | ---------- | ------------------------
`fanGetActive`               | "V6.0"        | yes*     | "fan"      | Fan Get Active - Mn or Vn.n
`fanSetActiveOn`             | "V6.1"        | yes*     | "fan"      | Fan Set Active to On - Mn or Vn.n
`fanSetActiveOff`            | "V6.2"        | yes*     | "fan"      | Fan Set Active to Off - Mn or Vn.n
`fanGetRotationDirection`    | "V6.3"        | no*      | "fan"      | Fan Get Rotation Direction - Mn or Vn.n
`fanSetRotationDirectionCW`  | "V6.4"        | no*      | "fan"      | Fan Set Rotation Direction to Clockwise - Mn or Vn.n
`fanSetRotationDirectionCCW` | "V6.5"        | no*      | "fan"      | Fan Set Rotation Direction to Counter Clockwise - Mn or Vn.n
`fanGetRotationSpeed`        | "VW60"        | no*      | "fan"      | Fan Get Rotation Speed - AMn or VWn
`fanSetRotationSpeed`        | "VW62"        | no*      | "fan"      | Fan Set Rotation Speed - AMn or VWn

```json
{
    "name": "Item-12",
    "type": "fan",
    "fanGetActive": "V6.0",
    "fanSetActiveOn": "V6.1",
    "fanSetActiveOff": "V6.2",
    "fanGetRotationDirection": "V6.3",
    "fanSetRotationDirectionCW": "V6.4",
    "fanSetRotationDirectionCCW": "V6.5",
    "fanGetRotationSpeed": "VW60",
    "fanSetRotationSpeed": "VW62"
}
```

## Filter Maintenance Configuration ##

__:construction: In HomeKit Accessory Protocol Specification available but currently not supported by the Home-App!__

Name                     | Value             | Required | Option for | Notes
------------------------ | ----------------- | -------- | ---------- | ------------------------
`filterChangeIndication`      | "V7.0"       | yes*     | "filterMaintenance" | Filter Maintenance Get Filter Change Indication - Mn or Vn.n
`filterLifeLevel`             | "VW64"       | no*      | "filterMaintenance" | Filter Maintenance Get Filter Life Level - AMn or VWn
`filterResetFilterIndication` | "V7.1"       | no*      | "filterMaintenance" | Filter Maintenance Set Reset Filter Indication - Mn or Vn.n

```json
{
    "name": "Item-13",
    "type": "filterMaintenance",
    "filterChangeIndication": "V7.0",
    "filterLifeLevel": "VW64",
    "filterResetFilterIndication": "V7.1"
}
```
  
## Example Configuration ##  

`bridge.cfg` file on SD card. [JSON]
  
```json
{
    "port": 502,
    "plcs": [
        {
            "name": "Logo 1",
            "ip": "192.168.001.100",
            "items": [
                {
                    "name": "Item-1",
                    "type": "switch",
                    "pushButton": 1,
                    "switchGet": "Q1",
                    "switchSetOn": "V1.0",
                    "switchSetOff": "V1.1"
                },
                {
                    "name": "Item-2",
                    "type": "switch",
                    "switchGet": "Q2",
                    "switchSetOn": "V1.2",
                    "switchSetOff": "V1.3"
                },
                {
                    "name": "Item-3",
                    "type": "switch",
                    "switchGet": "Q3",
                    "switchSetOn": "V1.4",
                    "switchSetOff": "V1.5"
                },
                {
                    "name": "Item-4",
                    "type": "switch",
                    "switchGet": "M1",
                    "switchSetOn": "V1.6",
                    "switchSetOff": "V1.7"
                },
                {
                    "name": "Item-5",
                    "type": "lightbulb",
                    "lightbulbGet": "Q4",
                    "lightbulbSetOn": "V2.0",
                    "lightbulbSetOff": "V2.1",
                    "lightbulbSetBrightness": "VW20",
                    "lightbulbGetBrightness": "VW22"
                },
                {
                    "name": "Item-6",
                    "type": "blind",
                    "blindConvertValue": 1,
                    "blindSetTargetPos": "VW26",
                    "blindGetTargetPos": "VW26",
                    "blindGetPos": "VW28",
                    "blindGetState": "VW30"
                },
                {
                    "name": "Item-7",
                    "type": "window",
                    "windowConvertValue": 1,
                    "windowSetTargetPos": "VW32",
                    "windowGetTargetPos": "VW32",
                    "windowGetPos": "VW34",
                    "windowGetState": "VW36"
                },
                {
                    "name": "Item-8",
                    "type": "garagedoor",
                    "garagedoorGetState": "VW40",
                    "garagedoorGetTargetState": "VW40",
                    "garagedoorSetTargetState": "VW38",
                    "garagedoorObstruction": "V3.0"
                },
                {
                    "name": "Item-9",
                    "type": "thermostat",
                    "thermostatGetHCState": "VW42",
                    "thermostatGetTargetHCState": "VW44",
                    "thermostatSetTargetHCState": "VW46",
                    "thermostatGetTemp": "VW48",
                    "thermostatGetTargetTemp": "VW50",
                    "thermostatSetTargetTemp": "VW52",
                    "thermostatTempDisplayUnits": 0
                },
                {
                    "name": "Item-10",
                    "type": "irrigationSystem",
                    "irrigationSystemGetActive": "V4.0",
                    "irrigationSystemSetActiveOn": "V4.1",
                    "irrigationSystemSetActiveOff": "V4.2",
                    "irrigationSystemGetProgramMode": "VW54",
                    "irrigationSystemGetInUse": "V4.3"
                },
                {
                    "name": "Item-11",
                    "type": "valve",
                    "valveGetActive": "V5.0",
                    "valveSetActiveOn": "V5.1",
                    "valveSetActiveOff": "V5.2",
                    "valveGetInUse": "V5.3",
                    "valveType": 1,
                    "valveSetDuration": "VW56",
                    "valveGetDuration": "VW56",
                    "valveGetRemainingDuration": "VW58"
                },
                {
                    "name": "Item-12",
                    "type": "fan",
                    "fanGetActive": "V6.0",
                    "fanSetActiveOn": "V6.1",
                    "fanSetActiveOff": "V6.2",
                    "fanGetRotationDirection": "V6.3",
                    "fanSetRotationDirectionCW": "V6.4",
                    "fanSetRotationDirectionCCW": "V6.5",
                    "fanGetRotationSpeed": "VW60",
                    "fanSetRotationSpeed": "VW62"
                },
                {
                    "name": "Item-13",
                    "type": "filterMaintenance",
                    "filterChangeIndication": "V7.0",
                    "filterLifeLevel": "VW64",
                    "filterResetFilterIndication": "V7.1"
                }
            ]
        }
    ]
}
```  
  