# Arduino fastled
## Mqtt driver for digital led

Driver for LED stripes (WS2812 and similar). This project is continuation of H801 drivers:
* [python](https://github.com/ter-haar/h801_mqtt_light)
* [lua](https://github.com/ter-haar/lua_mqtt_light).

I was bored with programming H801. WS2812 are easiest to program in Arduino (it has most broaden library).

This project is loosely based on [ESP-MQTT-JSON-Digital-LEDs](https://github.com/bruhautomation/ESP-MQTT-JSON-Digital-LEDs), You can use any chip you want with ESP8266 controller (personally I am using Wemos D1 Mini, due to ease in soldering + they have built in controller 5 -> 3.3 V).

-------------------
* [Setup](docs/install_en.md)
* [Home Assistant configuration](docs/hass_en.md)
* [Mqtt](docs/mqtt_en.md)
