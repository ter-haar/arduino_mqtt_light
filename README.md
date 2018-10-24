# arduino_mqtt_light


setBrightness
blur1d( leds, NUM_LEDS, animate.speed);

mosquitto_pub -h 192.168.24.115 -t home/light/ARDUINO-3104834/set -m '{"speed": 4, "p1": 3, "p2": 4, "p3": 5}'
