## Home Assistant configuration

Example configuration of the Home Assistant:

```
  - platform: mqtt_json
    name: sypialnia-rgb
    state_topic: "home/light/ARDUINO-2779185/status"
    command_topic: "home/light/ARDUINO-2779185/set"
    availability_topic: "home/light/ARDUINO-2779185/info"
    brightness: true
    rgb: true
    effect: true
    effect_list: [solid, rainbow, sinelon, sinelon rgb, glitter, glitter rgb, blur, gradients]
    retain: true
```
