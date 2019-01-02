## Arduino mqtt digital led

* turn on
```
home/light/ARDUINO-2779185/set {"state": "ON"}
```

* turn off
```
home/light/ARDUINO-2779185/status {"state":"OFF"}
```

* turn on, set colour, set brightness
```
home/light/ARDUINO-2779185/set {"color": {"g": 0, "r": 130, "b": 0}, "state": "ON"}
```

* turn on, change the effect
```
home/light/ARDUINO-2779185/set {"state": "ON", "effect": "gradients"}
```

* change the parameters p1, p2, p3 (depends on the chosen effect)
```
home/light/ARDUINO-2779185/set {"p1": 1, "p2": 2, "p3": 3}
```

* change the speed (depends on the chosen effect)
```
home/light/ARDUINO-2779185/set {"speed": 30}
```


