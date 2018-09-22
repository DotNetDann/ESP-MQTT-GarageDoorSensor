/* Add your keys & rename this file to auth.h */

#ifndef _AUTH_DETAILS
#define _AUTH_DETAILS

// Wifi Settings
#define WIFI_HOSTNAME "GarDoor"
#define WIFI_SSID "ssid"
#define WIFI_PASSWORD "password"

// MQTT Settings
#define MQTT_SERVER "mqtt server ip"
#define MQTT_USER ""
#define MQTT_PASSWORD ""
#define MQTT_PORT 1883
#define MQTT_AVAIL_TOPIC WIFI_HOSTNAME "/availability"

// OTA Settings for pushing updated software
#define OTApassword "ota password" //the password you will need to enter to upload remotely via the ArduinoIDE
#define OTAport 8266

// Distance Parameters
#define ULTRASONIC_MAX_DISTANCE 400 // Maximum distance (in cm) to ping.
#define ULTRASONIC_DIST_MAX_OPEN 70 // cm
#define ULTRASONIC_DIST_MAX_CAR 120 // cm
#define ULTRASONIC_TIMEOUT 40000 // µs
#define VERIFICATION_INTERVAL 30 // ms that the state must stay the same before it is reported
#define RELAY_ACTIVE_TIMEOUT 500 // ms the time the relay will close to actuate the door opener
#define DOOR_TRIG_PIN 2 // D4 on ESP8266

// Door 1 Parameters
#define DOOR1_ALIAS "Door 1"
#define MQTT_DOOR1_ACTION_TOPIC WIFI_HOSTNAME "/1/action"
#define MQTT_DOOR1_STATUS_TOPIC WIFI_HOSTNAME "/1/status"
#define DOOR1_RELAY_PIN 10 // SD3 on ESP8266
#define DOOR1_ECHO_PIN 14 // D5 on ESP8266

// Door 2 Parameters
#define DOOR2_ENABLED true
#define DOOR2_ALIAS "Door 2"
#define MQTT_DOOR2_ACTION_TOPIC WIFI_HOSTNAME "/2/action"
#define MQTT_DOOR2_STATUS_TOPIC WIFI_HOSTNAME "/2/status"
#define DOOR2_RELAY_PIN 4 // D2 on ESP8266
#define DOOR2_ECHO_PIN 12 // D6 on ESP8266

// Door 3 Parameters
#define DOOR3_ENABLED true
#define DOOR3_ALIAS "Door 3"
#define MQTT_DOOR3_ACTION_TOPIC WIFI_HOSTNAME "/3/action"
#define MQTT_DOOR3_STATUS_TOPIC WIFI_HOSTNAME "/3/status"
#define DOOR3_RELAY_PIN 5 // D1 on ESP8266
#define DOOR3_ECHO_PIN 13 // D7 on ESP8266

// DHT Parameters
#define DHT_ENABLED true
#define DHT_PIN 15 // D8 on ESP8266
#define DHT_TYPE DHT22 // or: DHT21 or DHT22
#define MQTT_TEMPERATURE_TOPIC WIFI_HOSTNAME "/temperature"
#define MQTT_HUMIDITY_TOPIC WIFI_HOSTNAME "/humidity"
#define DHT_PUBLISH_INTERVAL 300
#define DHT_TEMPERATURE_CELSIUS true
#define DHT_TEMPERATURE_ALIAS "Garage Temperature"
#define DHT_HUMIDITY_ALIAS "Garage Humidity"

#endif
