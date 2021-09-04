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
`lightbulbSetBrightness` | "VW20"              | yes*     | "lightbulb" | Lightbulb Set Brightness - AMn or VWn
`lightbulbGetBrightness` | "VW22"              | yes*     | "lightbulb" | Lightbulb Get Brightness - AMn or VWn

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
`blindSetPos`            | "VW26"              | yes*     | "blind"    | Blind Set Pos - AMn or VWn
`blindGetPos`            | "VW28"              | yes*     | "blind"    | Blind Get Pos - AMn or VWn
`blindSetState`          | "VW30"              | yes*     | "blind"    | Blind Get State - AMn or VWn
`blindConvertValue`      | 0 or 1              | no       | "blind"    | Convert LOGO! values in to HomeKit values, default is: 1.  
  
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
                }
            ]
        }
    ]
}
```  
  