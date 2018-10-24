#include <ArduinoJson.h>

#define BUFFER_SIZE JSON_OBJECT_SIZE(10)
#define MQTT_MAX_PACKET_SIZE 512

// todo
// do we really need this status?
struct status_struct {
    String      state = "OFF";
    String      effect = "solid";
    bool        on = false;
    int         brightness = 255;
    int         speed = 10;
    CRGB        color = CRGB::White;
} status;


void mqtt_callback(char* topic, byte* payload, unsigned int length) {
    digitalWrite(myconf.status_led, LOW);

    //convert payload to string, and 0 terminate
    char message[length + 1];
    strncpy(message, (char*)payload, length);
    message[length] = 0;

    Serial.print("Message [");
    Serial.print(topic);
    Serial.print("] ");
    Serial.println(message);

    char* last_token;
    char* previous_token;
    char* position = strtok(topic, "/");
    last_token = position;
    while(position != NULL){
        previous_token = last_token;
        last_token = position;
        position = strtok(NULL, "/");
    }

    if (strcmp(last_token, "set") == 0) {
        processJson(message);
    }

    digitalWrite(myconf.status_led, HIGH);
}


bool processJson(char* message) {
    StaticJsonBuffer<BUFFER_SIZE> inputBuffer;
    JsonObject& input = inputBuffer.parseObject(message);

    if (!input.success()) {
        Serial.println("parseObject() failed");
        return false;
    }

    StaticJsonBuffer<BUFFER_SIZE> outputBuffer;
    JsonObject& output = outputBuffer.createObject();

    if (input.containsKey("color")) {
        char r = input["color"]["r"];
        char g = input["color"]["g"];
        char b = input["color"]["b"];
        status.color = CRGB(r, g, b);
        animate.set_color(status.color);

        JsonObject& color = output.createNestedObject("color");
        color["r"] = r;
        color["g"] = g;
        color["b"] = b;
    }

    if (input.containsKey("state")) {
        if (strcmp(input["state"], "ON") == 0) {
            if (status.on == false) {
                animate.set_on();
            }
            status.on = true;
            status.state = "ON";
            output["state"] = "ON";
        }
        else if (strcmp(input["state"], "OFF") == 0) {
            if (status.on == true) {
                animate.set_off();
            }
            status.on = false;
            status.state = "OFF";
            output["state"] = "OFF";
        }
    }

    if (input.containsKey("effect")) {
        status.effect = (const char*)input["effect"];
        output["effect"] = status.effect.c_str();
        animate.set_effect(status.effect.c_str());
    }

    if (input.containsKey("brightness")) {
        status.brightness = input["brightness"];
        output["brightness"] = status.brightness;
        animate.set_brightness(status.brightness);
    }

    if (input.containsKey("speed")) {
        status.speed = input["speed"];
        output["speed"] = status.speed;
        animate.speed = input["speed"];
    }

    // todo
    // use list/loop/for {'p1', 'p2', 'p3'}
    if (input.containsKey("p1")) {
        output["p1"] = input["p1"];
        animate.p1 = input["p1"];
    }

    if (input.containsKey("p2")) {
        output["p2"] = input["p2"];
        animate.p2 = input["p2"];
    }

    if (input.containsKey("p3")) {
        output["p3"] = input["p3"];
        animate.p3 = input["p3"];
    }

    animate.start();

    // ---------------------- send status mqtt message -------------------------
    char buffer[output.measureLength() + 1];
    output.printTo(buffer, sizeof(buffer));

    // todo
    String id = String(ESP.getChipId());
    String topic = String(myconf.mqtt_topic) + id + "/";
    mqtt.publish(String(topic + "status").c_str(), buffer, false);
    return true;
}


// String getStatusString() {
//     StaticJsonBuffer<BUFFER_SIZE> outputBuffer;
//     JsonObject& output = outputBuffer.createObject();

//     output["state"] = status.state.c_str();

//     JsonObject& color = output.createNestedObject("color");
//     color["r"] = status.color.r;
//     color["g"] = status.color.g;
//     color["b"] = status.color.b;

//     output["effect"] = status.effect.c_str();
//     output["brightness"] = status.brightness;

//     char buffer[output.measureLength() + 1];
//     output.printTo(buffer, sizeof(buffer));
//     return String(buffer);
// }
