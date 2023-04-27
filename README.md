# arduino-fmt - use [fmt](https://fmt.dev/8.1.1/) from Arduino Streams

this is a wrapper around Print() to make fmt usable for Arduino Streams.

## usage

see [the example](examples/fmttest.cpp) 

Fmt adds a single method:  `Fmt::fmt(format_string, args..)`

## example:

`````
#include <Arduino.h>
#include <Fmt.h>

Fmt f(&Serial);
// Fmt f(Serial); // works too

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    yield();
  }
  f.fmt("{}{}\n", "foo", 4711);
  // all methods from Print still work:
  f.printf("%f %s\n", 3.14, "foo");
}

void loop() { yield(); }
````

## fmt library

tested with the Platformio fmt library: https://registry.platformio.org/libraries/fmtlib/fmt

see also: https://github.com/werediver/fmtlib_pio
