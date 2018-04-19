# ESP8266 MQTT GarageDoorSensor HomeAssistant
=====================
This project allows three "dumb" garage door openers to be controlled (open/close) and report garage door status (open/closed/occupied) via MQTT.

The code covered in this repository utilizes [Home Assistant's MQTT Cover Component](https://www.home-assistant.io/components/cover.mqtt/) and uses an ESP8266 microcontroller. There is a sample configuration in the repository

Inspiration for this comes from GarHAge and OpenGarage.


#### Supported Features Include
- Report status on up to 3 garage doors
- Web page for status
- Events and status sent via MQTT
- MQTT commands to toggle relays to open/close the garage doors
- Over-the-Air (OTA) Upload from the ArduinoIDE!


#### OTA Uploading
This code also supports remote uploading to the ESP8266 using Arduino's OTA library. To utilize this, you'll need to first upload the sketch using the traditional USB method. However, if you need to update your code after that, your WIFI-connected ESP chip should show up as an option under Tools -> Port -> Porch at your.ip.address.xxx. More information on OTA uploading can be found [here](http://esp8266.github.io/Arduino/versions/2.0.0/doc/ota_updates/ota_updates.html). Note: You cannot access the serial monitor over WIFI at this point.  


#### Parts List
- [NodeMCU](https://www.amazon.com/HiLetgo-Version-NodeMCU-Internet-Development/dp/B010O1G1ES/)
- [3x HC-SR04 Ultrasonic Sensors](http://au.element14.com/mcm/83-17989/hc-sr04-ultrasonic-sensor-for/dp/2801408?ost=HC-SR04)
- [5V 4 Channel Relay Board](https://www.ebay.com.au/sch/i.html?_from=R40&_trksid=p2380057.m570.l1313.TR0.TRC0.H0.X5V+4+Channel+Relay+Board.TRS0&_nkw=5V+4+Channel+Relay+Board&_sacat=0)


#### Wiring Diagram
![alt text](https://github.com/DotNetDann/ESP-MQTT-GarageDoorSensor/blob/master/Wiring%20Diagram.png?raw=true "Wiring Diagram")


#### Sample MQTT commands
Listen to MQTT commands
> mosquitto_sub -h 172.17.0.1 -t '#'

Open the second garage door
> mosquitto_pub -h 172.17.0.1 -t GarDoor/2/action -m "OPEN"
