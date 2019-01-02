## Arduino mqtt digital led

To compile the code [arduino ide](https://www.arduino.cc/en/Main/Software) is required.

In Arduino IDE you need to install libraries below:
* FastLED
* PubSubClient
* ArduinoJSON

------------------------------

1) Clone/copy this repository
2) Edit configuration in file config.h.sample and save as config.h
3) Compile and load it to the controller

If there are any problems during the animation (eg. LED is blinking, dimming out or working unstable, please read:
https://github.com/bruhautomation/ESP-MQTT-JSON-Digital-LEDs/issues/60.

To solve this problem FastLED DMA library is required: [FastLED DMA](https://github.com/coryking/FastLED)

> To fix the behavior seen here, download the fork https://github.com/coryking/FastLED to a zip file named FastLED.zip and import to your Arduino IDE. Then in your controller code add the line #define FASTLED_ESP8266_DMA to the top of your code, as well as changing the pin to 3 (and adjust the wiring on your chip to use the RX pin). You should also remove any interrupt bypassing (#define FASTLED_ALLOW_INTERRUPTS 0).
