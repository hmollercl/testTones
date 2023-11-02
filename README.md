# testTones
Test tone generator to experiment

to build:
```gcc -fvisibility=hidden -fPIC -Wl,-Bstatic -Wl,-Bdynamic -Wl,--as-needed -shared -pthread `pkg-config --cflags lv2` -lm `pkg-config --libs lv2` testTones.c -o testTones.so```

needed in ubuntu:
```sudo apt install build-essential pkg-config lv2-dev```
