# Arduino fastled
## Sterownik mqtt digital led.

Sterownik cyfrowych pasków ledowych (układy ws2812 i podobne). Ten projekt to kontynuacja sterowników H801:
* [python](https://github.com/ter-haar/h801_mqtt_light)
* [lua](https://github.com/ter-haar/lua_mqtt_light)

Znudziło mi się programowanie H801, diody ws2812 najprościej programować w arduino (ma najbardziej rozbudowaną bibliotekę).

Ten projekt jest luźno wzorowany na [ESP-MQTT-JSON-Digital-LEDs](https://github.com/bruhautomation/ESP-MQTT-JSON-Digital-LEDs), podobnie jak tam można użyć dowolnego układu z kontrolerem ESP8266 (ja używam wemos d1 mini, bo się je łatwo lutuje i mają wbudowany konwerter napięcia 5v -> 3.3v)

-------------------
* [Opis instalacji](docs/install_pl.md)
* [Konfiguracja HomeAssistanta](docs/hass_pl.md)
* [Mqtt](docs/mqtt_pl.md)
