## Arduino mqtt digital led

* włączenie
```
home/light/ARDUINO-2779185/set {"state": "ON"}
```

* wyłączenie
```
home/light/ARDUINO-2779185/status {"state":"OFF"}
```

* włączenie, ustawienie koloru, ustawienie jasności
```
home/light/ARDUINO-2779185/set {"color": {"g": 0, "r": 130, "b": 0}, "state": "ON"}
```

* włączenie, zmiana efektu
```
home/light/ARDUINO-2779185/set {"state": "ON", "effect": "gradients"}
```

* zmiana parametrów p1, p2, p3 (znaczenie zależne od aktualnie wybranego efektu)
```
home/light/ARDUINO-2779185/set {"p1": 1, "p2": 2, "p3": 3}
```

* zmiana szybkości (znaczenie zależne od aktualnie wybranego efektu)
```
home/light/ARDUINO-2779185/set {"speed": 30}
```
