# ESP8266 MQTT GarageDoorSensor and Temperture HomeAssistant
=====================
This project allows for up to  three "dumb" garage door openers to be controlled (open/close) and report garage door status (open/closed/occupied) via MQTT. In addition if you can also monitor the Temperture and Humidity within your garage to over MQTT as well.

The code covered in this repository utilizes [Home Assistant's MQTT Cover Component](https://www.home-assistant.io/components/cover.mqtt/) and uses an ESP8266 microcontroller. There is a sample configuration in the repository

Inspiration for this comes from GarHAge and OpenGarage. I orginally forked this from https://github.com/DotNetDann/ESP-MQTT-GarageDoorSensor, and added the Temp and Humidity code for a DHT22 from GarHage, and now it morphed to change to NewPing for the ultrasonic HC-SR04 due to the inconsitant reading using the Ultrasonic library with the HC-SCR04 I aquired from china.

**NOTE:** I am currrently only using this with one garage door, to enable for 2 or 3, just enable the use to true in the auth.h file you create

#### Supported Features Include
- Report status on up to 3 garage doors
- Report information on Temp and Humidity
- Ability to Select Celius or Fahrenheit for Temp
- Web page for status of Garage Doors and Temperature
- Events and status sent via MQTT
- MQTT commands to toggle relays to open/close the garage doors
- Over-the-Air (OTA) Upload from the ArduinoIDE!


#### OTA Uploading
This code also supports remote uploading to the ESP8266 using Arduino's OTA library. To utilize this, you'll need to first upload the sketch using the traditional USB method. However, if you need to update your code after that, your WIFI-connected ESP chip should show up as an option under Tools -> Port -> 'HostName'at your.ip.address.xxx. 

More information on OTA uploading can be found [here](http://esp8266.github.io/Arduino/versions/2.0.0/doc/ota_updates/ota_updates.html). 


#### Parts List
- [NodeMCU](https://www.amazon.com/HiLetgo-Version-NodeMCU-Internet-Development/dp/B010O1G1ES/)
- [1-3 x HC-SR04 Ultrasonic Sensors]() Depending on how many Doors you will monitor
- [5V 4 Channel Relay Board](https://www.ebay.com./sch/i.html?_from=R40&_trksid=p2380057.m570.l1313.TR0.TRC0.H0.X5V+4+Channel+Relay+Board.TRS0&_nkw=5V+4+Channel+Relay+Board&_sacat=0) If Controling 2 or More Garage Doors this is the best choice
- Otherwise buy a Single Relay for a singe Door
	[5V 1 Channel Relay Board](https://www.ebay.com./sch/i.html?_from=R40&_trksid=p2380057.m570.l1313.TR0.TRC0.H0.X5V+1+Channel+Relay+Board.TRS0&_nkw=5V+1+Channel+Relay+Board&_sacat=0)

#### Wiring Diagram
![alt text](https://github.com/iceman73/ESP-MQTT-GarageDoorSensor/blob/master/Wiring%20Diagram.png?raw=true "Wiring Diagram")


#### Web page
![alt text](https://github.com/iceman73/ESP-MQTT-GarageDoorSensor/blob/dev/Webpage-with-Temp.png?raw=true "Web Page with Temp")
![alt text](https://github.com/iceman73/ESP-MQTT-GarageDoorSensor/blob/master/WebpageStatus.png?raw=true "Webpage Status")


#### Sample MQTT commands
Listen to MQTT commands
> mosquitto_sub -h 172.17.0.1 -t '#'

Open the second garage door
> mosquitto_pub -h 172.17.0.1 -t GarDoor/2/action -m "OPEN"

