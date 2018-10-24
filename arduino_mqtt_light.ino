/*
  To use this code you will need the following dependancies:

  - Support for the ESP8266 boards.
        - You can add it to the board manager by going to File -> Preference and pasting http://arduino.esp8266.com/stable/package_esp8266com_index.json into the Additional Board Managers URL field.
        - Next, download the ESP8266 dependancies by going to Tools -> Board -> Board Manager and searching for ESP8266 and installing it.

  - You will also need to download the follow libraries by going to Sketch -> Include Libraries -> Manage Libraries
      - FastLED
      - PubSubClient
      - ArduinoJSON
*/

/*
todo:
load config file from serial

    strchr(): search for a character in a C string (i.e. char *)
    strtok(): splits a C string into substrings, based on a separator character
    atoi(): converts a C string to an int
*/


#define FASTLED_ESP8266_DMA

#include <ESP8266WiFi.h>
// #include <ESP8266mDNS.h>
#include <Arduino.h>
// #include <ArduinoOTA.h>
#include <PubSubClient.h>
#include <FastLED.h>

// #include "setup.h"
#include "config.h"

// ================================== GLOBALS ==================================
WiFiClient espClient;
PubSubClient mqtt(espClient);
CRGB leds[NUM_LEDS];

// ==================================  SETUP  ==================================
void setup() {
    setup_serial();
    setup_leds(leds);
    setup_wifi();
    setup_mqtt(mqtt_callback);
}


// ================================= MAIN LOOP =================================
void loop() {
    if (WiFi.status() != WL_CONNECTED) {
        Serial.print("WIFI Disconnected. Attempting reconnection.");
        setup_wifi();
    }

    if (!mqtt.connected()) {
        mqtt_connect();
    }

    mqtt.loop();
    animate_loop(leds);
    // ArduinoOTA.handle();
}
