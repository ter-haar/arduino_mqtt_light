extern config_struct myconf;
extern PubSubClient mqtt;

void setup_serial(void) {
    Serial.begin(115200);
    Serial.println("");
    Serial.print("Chip ID: ");
    Serial.println(ESP.getChipId());
}


void setup_leds(CRGB *leds) {
    pinMode(myconf.status_led, OUTPUT);
    digitalWrite(myconf.status_led, HIGH);

    FastLED.addLeds<CHIPSET, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
    FastLED.clear();
    FastLED.show();
}


void setup_wifi(void) {
    Serial.print("Connecting to ");
    Serial.println(myconf.wifi_ssid);

    WiFi.mode(WIFI_STA);
    WiFi.begin(myconf.wifi_ssid, myconf.wifi_password);

    while (WiFi.status() != WL_CONNECTED) {
        digitalWrite(myconf.status_led, LOW);
        delay(100);
        digitalWrite(myconf.status_led, HIGH);
        delay(100);
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    Serial.print("Mac Address: ");
    Serial.println(WiFi.macAddress());
}


void setup_mqtt(void (*callback)(char*, uint8_t*, unsigned int)) {
    mqtt.setServer(myconf.mqtt_server, myconf.mqtt_port);
    mqtt.setCallback(callback);
}


void mqtt_connect(void) {
    String id = String(ESP.getChipId());
    String topic = String(myconf.mqtt_topic) + id + "/";
    while (!mqtt.connected()) {
        Serial.print("Attempting MQTT connection...");
        if (mqtt.connect(
                id.c_str(), myconf.mqtt_username, myconf.mqtt_password,
                String(topic + "info").c_str(), 0, true, "offline"
            )) {
            Serial.println("connected");
            mqtt.publish(String(topic + "ip").c_str(), WiFi.localIP().toString().c_str(), true);
            mqtt.publish(String(topic + "info").c_str(), "online", true);
            // mqtt.publish(String(topic + "status").c_str(), getStatusString().c_str(), true);

            mqtt.subscribe(String(topic + "#").c_str());
        } else {
            Serial.print("failed, rc=");
            Serial.print(mqtt.state());
            Serial.println(" try again in 5 seconds");
            // 5 seconds delay, blinking led
            for (int i=0; i<10; i++) {
                digitalWrite(myconf.status_led, LOW);
                delay(250);
                digitalWrite(myconf.status_led, HIGH);
                delay(250);
            }
        }
    }
}

