## Arduino mqtt digital led

Do skompilowania kodu wymagane jest [arduino ide](https://www.arduino.cc/en/Main/Software). 

W arduino IDE musisz zainstalować biblioteki:
* FastLED
* PubSubClient
* ArduinoJSON

------------------------------

1) Sklonuj/skopiuj to repozytorium.
2) Edytuj konfiguracje w pliku config.h.sample, zapisz jako config.h
3) Skompiluj, załaduj do kontrolera.

Jeżeli podczas animiacji diody migoczą, przygasają i ogólnie całość jest niestabilna polecam przeczytać:
https://github.com/bruhautomation/ESP-MQTT-JSON-Digital-LEDs/issues/60. 

Remedium na te problemy jest instalacja biblioteki [FastLED DMA](https://github.com/coryking/FastLED)

> To fix the behavior seen here, download the fork https://github.com/coryking/FastLED to a zip file named FastLED.zip and import to your Arduino IDE. Then in your controller code add the line #define FASTLED_ESP8266_DMA to the top of your code, as well as changing the pin to 3 (and adjust the wiring on your chip to use the RX pin). You should also remove any interrupt bypassing (#define FASTLED_ALLOW_INTERRUPTS 0).
