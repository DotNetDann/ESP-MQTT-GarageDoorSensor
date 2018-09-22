/*
  To use this code you will need the following dependencies:

  - Support for the ESP8266 boards.
        - You can add it to the board manager by going to File -> Preference and pasting http://arduino.esp8266.com/stable/package_esp8266com_index.json into the Additional Board Managers URL field.
        - Next, download the ESP8266 dependencies by going to Tools -> Board -> Board Manager and searching for ESP8266 and installing it.

  - You will also need to download the follow libraries by going to Sketch -> Include Libraries -> Manage Libraries
      - NewPing
      - PubSubClient
      - ArduinoJSON

  - Another like project https://hackaday.io/project/25090/instructions
  - Where this code was forked from https://github.com/DotNetDann/ESP-MQTT-GarageDoorSensor
*/
// 1.4 Changes to use NewPing
// 1.3 adds DHT Sensor for Temp and Humidty

// ------------------------------
// ---- all config in auth.h ----
// ------------------------------
#define VERSION F("v1.5 - GarDoor - https://github.com/DotNetDann - http://dotnetdan.info")

#include <ArduinoJson.h> // Benoit Blanchon
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <PubSubClient.h> // Nick O'Leary
#include <NewPing.h> // Tim Eckel
#include <ArduinoOTA.h>
#include <DHT.h> // Adafruit
#include <Adafruit_Sensor.h> // Adafruit Unified Sensor
#include "auth.h"

#define DOOR_UNKNOWN         0x00
#define DOOR_OPENED          0x01
#define DOOR_CLOSEDNOCAR     0x02
#define DOOR_CLOSEDWITHCAR   0x03
#define SONAR_NUM 3      // Number of sensors.


/**************************************** GLOBALS ***************************************/
const int BUFFER_SIZE = JSON_OBJECT_SIZE(10);
#define MQTT_MAX_PACKET_SIZE 512

int door1_lastDistanceValue = 0;
int door2_lastDistanceValue = 0;
int door3_lastDistanceValue = 0;

char* birthMessage = "online";
const char* lwtMessage = "offline";

const char* dhtTempTopic = MQTT_TEMPERATURE_TOPIC;
const char* dhtHumTopic = MQTT_HUMIDITY_TOPIC;
const unsigned long dht_publish_interval_s = DHT_PUBLISH_INTERVAL;
unsigned long dht_lastReadTime = -1000;

/******************************** GLOBAL OBJECTS *******************************/

NewPing sonar[SONAR_NUM] = {   // Sensor object array.
  NewPing(DOOR_TRIG_PIN, DOOR1_ECHO_PIN, ULTRASONIC_MAX_DISTANCE), // Each sensor's trigger pin, echo pin, and max distance to ping. 0-2
  NewPing(DOOR_TRIG_PIN, DOOR2_ECHO_PIN, ULTRASONIC_MAX_DISTANCE), 
  NewPing(DOOR_TRIG_PIN, DOOR3_ECHO_PIN, ULTRASONIC_MAX_DISTANCE)
};

WiFiClient espClient;
PubSubClient client(espClient);
ESP8266WebServer server(80);
DHT dht(DHT_PIN, DHT_TYPE);

// Get the state of the garage based upon the sensor distance
byte getState(int distance)
{
  if (distance <= 1) {
    return DOOR_UNKNOWN; // Should not ever be this close. Probably an error
  } else if (distance <= ULTRASONIC_DIST_MAX_OPEN) {
    return DOOR_OPENED;
  } else if (distance <= ULTRASONIC_DIST_MAX_CAR) {
    return DOOR_CLOSEDWITHCAR;
  } else {
    return DOOR_CLOSEDNOCAR;
  }
}

#include "web.h"

/********************************** START SETUP *****************************************/
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);       // Initialize the LED_BUILTIN pin as an output (So it doesnt float as a LED is on this pin)
  digitalWrite(LED_BUILTIN, LOW);     // Turn the status LED on

  Serial.begin(115200);
  delay(10);
  Serial.println(F("Starting..."));

  // Setup Door 1 pins
  pinMode(DOOR1_RELAY_PIN, OUTPUT);
  digitalWrite(DOOR1_RELAY_PIN, HIGH);

  #if DOOR2_ENABLED == true
    pinMode(DOOR2_RELAY_PIN, OUTPUT);
    digitalWrite(DOOR2_RELAY_PIN, HIGH);
  #endif

  #if DOOR3_ENABLED == true
    pinMode(DOOR3_RELAY_PIN, OUTPUT);
    digitalWrite(DOOR3_RELAY_PIN, HIGH);
  #endif

  setup_wifi();

  client.setServer(MQTT_SERVER, MQTT_PORT);
  client.setCallback(callback);

  server.on("/", ServeWebClients);
  server.begin();

  //OTA SETUP
  ArduinoOTA.setPort(OTAport);
  ArduinoOTA.setHostname(WIFI_HOSTNAME); // Hostname defaults to esp8266-[ChipID]
  ArduinoOTA.setPassword((const char *)OTApassword); // No authentication by default

  ArduinoOTA.onStart([]() {
    Serial.println("Starting");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();

  Serial.println(F("Ready"));
  digitalWrite(LED_BUILTIN, HIGH);     // Turn the status LED off
}


/********************************** START SETUP WIFI *****************************************/
void setup_wifi() {
  delay(10);
  Serial.print(F("Connecting to SSID: "));
  Serial.println(WIFI_SSID);

  // We start by connecting to a WiFi network
  WiFi.mode(WIFI_STA);
  //wifi_set_sleep_type(LIGHT_SLEEP_T); // Enable light sleep
  WiFi.hostname(WIFI_HOSTNAME);

  if (WiFi.status() != WL_CONNECTED) {  // FIX FOR USING 2.3.0 CORE (only .begin if not connected)
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  }

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }

  Serial.println(F(""));
  Serial.println(F("WiFi connected"));
  Serial.print(F("IP address: "));
  Serial.println(WiFi.localIP());
}


/********************************** START CALLBACK *****************************************/
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.println(F(""));
  Serial.print(F("Message arrived ["));
  Serial.print(topic);
  Serial.print(F("] "));

  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  String topicToProcess = topic;
  payload[length] = '\0';
  String payloadToProcess = (char*)payload;

  // Action Command
  if (payloadToProcess == "OPEN") {
    Serial.print(F("Triggering OPEN relay!"));
    if (topicToProcess == MQTT_DOOR1_ACTION_TOPIC) {
      toggleRelay(DOOR1_RELAY_PIN);
    } else if (topicToProcess == MQTT_DOOR2_ACTION_TOPIC) {
      toggleRelay(DOOR2_RELAY_PIN);
    } else if (topicToProcess == MQTT_DOOR3_ACTION_TOPIC) {
      toggleRelay(DOOR3_RELAY_PIN);
    }
    Serial.println(" -> DONE");
  }
  else if (payloadToProcess == "CLOSE") {
    Serial.print(F("Triggering CLOSE relay!"));
    if (topicToProcess == MQTT_DOOR1_ACTION_TOPIC) {
      toggleRelay(DOOR1_RELAY_PIN);
    } else if (topicToProcess == MQTT_DOOR2_ACTION_TOPIC) {
      toggleRelay(DOOR2_RELAY_PIN);
    } else if (topicToProcess == MQTT_DOOR3_ACTION_TOPIC) {
      toggleRelay(DOOR3_RELAY_PIN);
    }
    Serial.println(F(" -> DONE"));
  }
  else if (payloadToProcess == "STATE") {
    Serial.print(F("Publishing on-demand status update!"));
    Publish(MQTT_AVAIL_TOPIC, birthMessage);
    if (topicToProcess == MQTT_DOOR1_ACTION_TOPIC) {
      sendState(1);
    } else if (topicToProcess == MQTT_DOOR2_ACTION_TOPIC) {
      sendState(2);
    } else if (topicToProcess == MQTT_DOOR3_ACTION_TOPIC) {
      sendState(3);
    }
    Serial.println(F(" -> DONE"));
  } else {
    Serial.println(F("Unknown command!"));
  }
}


/********************************** START SEND STATE *****************************************/
void sendState(int door) {
  //{"state":"open","occupied":unknown,"distance":12,"name":"Door 1"}
  //{"state":"closed","occupied":true,"distance":1000,"name":"Door 2"}
  //{"state":"closed","occupied":false,"distance":2350,"name":"Door 3"}

  StaticJsonBuffer<BUFFER_SIZE> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();

  byte state = DOOR_UNKNOWN;
  char* topic = "";
  if (door == 1) {
    state = getState(door1_lastDistanceValue);
    topic = MQTT_DOOR1_STATUS_TOPIC;
    root["name"] = DOOR1_ALIAS;
    root["distance"] = door1_lastDistanceValue;
  } else if (door == 2) {
    state = getState(door2_lastDistanceValue);
    topic = MQTT_DOOR2_STATUS_TOPIC;
    root["name"] = DOOR2_ALIAS;
    root["distance"] = door2_lastDistanceValue;
  } else if (door == 3) {
    state = getState(door3_lastDistanceValue);
    topic = MQTT_DOOR3_STATUS_TOPIC;
    root["name"] = DOOR3_ALIAS;
    root["distance"] = door3_lastDistanceValue;
  } else {
    return;
  }

  char* doorState = "unknown";
  char* occupiedState = "unknown";
  if (state == DOOR_OPENED) {
    doorState = "open";
  } else if (state == DOOR_CLOSEDNOCAR) {
    doorState = "closed";
    occupiedState = "false";
  } else if (state == DOOR_CLOSEDWITHCAR) {
    doorState = "closed";
    occupiedState = "true";
  }
  root["state"] = doorState;
  root["occupied"] = occupiedState;

  char buffer[root.measureLength() + 1];
  root.printTo(buffer, sizeof(buffer));

  Publish(topic, buffer);

  // For HA. Cannot read JSON so send a simple state result also
  char* extraTopicState = "/value";
  char extraTopic[100];
  snprintf(extraTopic, sizeof extraTopic, "%s%s", topic, extraTopicState);
  Publish(extraTopic, doorState);
}

void Publish(char* topic, char* message) {
  client.publish(topic, message, true);

  //Print what was sent to console
  Serial.println(F(""));
  Serial.print(F("Published ["));
  Serial.print(topic);
  Serial.print(F("] "));
  Serial.println(message);
}

/********************************** START RELAY *****************************************/
void toggleRelay(int pin) {
    digitalWrite(pin, LOW);
    delay(RELAY_ACTIVE_TIMEOUT);
    digitalWrite(pin, HIGH);
}


/********************************** START RECONNECT *****************************************/
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print(F("Attempting MQTT connection..."));
    // Attempt to connect
    if (client.connect(WIFI_HOSTNAME, MQTT_USER, MQTT_PASSWORD, MQTT_AVAIL_TOPIC, 0, true, lwtMessage)) {
      Serial.println(F("connected"));

      // Publish the birth message on connect/reconnect
      Publish(MQTT_AVAIL_TOPIC, birthMessage);

      // Subscribe to the action topics to listen for action messages
      Serial.print(F("Subscribing to "));
      Serial.print(MQTT_DOOR1_ACTION_TOPIC);
      Serial.println(F("..."));
      client.subscribe(MQTT_DOOR1_ACTION_TOPIC);

      
      #if DOOR2_ENABLED == true
        Serial.print(F("Subscribing to "));
        Serial.print(MQTT_DOOR2_ACTION_TOPIC);
        Serial.println(F("..."));
        client.subscribe(MQTT_DOOR2_ACTION_TOPIC);
      #endif

      #if DOOR3_ENABLED == true
        Serial.print(F("Subscribing to "));
        Serial.print(MQTT_DOOR3_ACTION_TOPIC);
        Serial.println(F("..."));
        client.subscribe(MQTT_DOOR3_ACTION_TOPIC);
      #endif

      // Publish the current door status on connect/reconnect to ensure status is synced with whatever happened while disconnected
      door1_lastDistanceValue = 0;
      door2_lastDistanceValue = 0;
      door3_lastDistanceValue = 0;
      check_door_status();
       
    } else {
      Serial.print(F("failed, rc="));
      Serial.print(client.state());
      Serial.println(F(" try again in 5 seconds"));
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}


/********************************** START DOOR STATUS *****************************************/
void check_door_status() {

  // ---- Door 1 ----
  int distance = sonar[0].ping_cm();
  byte state = getState(distance);
  delay(VERIFICATION_INTERVAL);
  byte stateVerify = getState(sonar[0].ping_cm());

  Serial.print(distance);
  Serial.print(".");

  if ((distance > 0) && (state == stateVerify) && (state != getState(door1_lastDistanceValue))) {
    digitalWrite(LED_BUILTIN, LOW);     // Turn the status LED on
    door1_lastDistanceValue = distance;
    sendState(1);
    digitalWrite(LED_BUILTIN, HIGH);     // Turn the status LED off
  }


  // ---- Door 2 ----
  #if DOOR2_ENABLED == true
    distance = sonar[1].ping_cm();
    state = getState(distance);
    delay(VERIFICATION_INTERVAL);
    stateVerify = getState(sonar[1].ping_cm());

    Serial.print(distance);
    Serial.print(".");

    if ((distance > 0) && (state == stateVerify) && (state != getState(door2_lastDistanceValue))) {
      digitalWrite(LED_BUILTIN, LOW);     // Turn the status LED on
      door2_lastDistanceValue = distance;
      sendState(2);
      digitalWrite(LED_BUILTIN, HIGH);     // Turn the status LED off
    }
  #endif


  // ---- Door 3 ----
  #if DOOR3_ENABLED == true
    distance = sonar[2].ping_cm();
    state = getState(distance);
    delay(VERIFICATION_INTERVAL);
    stateVerify = getState(sonar[2].ping_cm());

    Serial.print(distance);
    Serial.print(".");

    if ((distance > 0) && (state == stateVerify) && (state != getState(door3_lastDistanceValue))) {
      digitalWrite(LED_BUILTIN, LOW);     // Turn the status LED on
      door3_lastDistanceValue = distance;
      sendState(3);
      digitalWrite(LED_BUILTIN, HIGH);     // Turn the status LED off
    }
  #endif

  Serial.println(".");
}

/*************************************DHT SENSOR*********************************************/


void dht_read_publish() {
  // Read values from sensor
  float hum = dht.readHumidity();
  float tempRaw = dht.readTemperature();

  // Check if there was an error reading values
  if (isnan(hum) || isnan(tempRaw)) {
    Serial.print("Failed to read from DHT sensor; will try again in ");
    Serial.print(dht_publish_interval_s);
    Serial.println(" seconds...");
    return;
  }

  boolean celsius = DHT_TEMPERATURE_CELSIUS;
  float temp;
  if (celsius) {
    temp = tempRaw;
  } else {
    temp = (tempRaw * 1.8 + 32);
  }
  
  char payload[4];

  // Publish the temperature payload via MQTT
  dtostrf(temp, 4, 0, payload);
  Serial.print("Publishing DHT Temperature payload: ");
  Serial.print(payload);
  Serial.print(" to ");
  Serial.print(dhtTempTopic);
  Serial.println("...");
  client.publish(dhtTempTopic, payload, false);
  // Publish the humidity payload via MQTT
  dtostrf(hum, 4, 0, payload);
  Serial.print("Publishing DHT Humidity payload: ");
  Serial.print(payload);
  Serial.print(" to ");
  Serial.print(dhtHumTopic);
  Serial.println("...");
  
  client.publish(dhtHumTopic, payload, false);
}


/********************************** START MAIN LOOP *****************************************/
void loop() {

  if (!client.connected()) {
    reconnect();
  }

  unsigned long currentTime = millis();
  
  if (WiFi.status() != WL_CONNECTED) {
    delay(1);
    Serial.print(F("WIFI Disconnected. Attempting reconnection."));
    setup_wifi();
    return;
  }

  client.loop(); // Check MQTT

  ArduinoOTA.handle(); // Check OTA Firmware Updates

  server.handleClient(); // Check Web page requests

  check_door_status(); // Check the sensors and publish any changes
  
  #if DHT_ENABLED == true
    if (currentTime - dht_lastReadTime > (dht_publish_interval_s * 1000)) {
      dht_read_publish();
      dht_lastReadTime = millis();
    }
  #endif
   
  //delay(500); // We have enabled Light sleep so this delay should reduce the power used
  delay(2000); // We have enabled Light sleep so this delay should reduce the power used
  //Serial.print(".");
}
