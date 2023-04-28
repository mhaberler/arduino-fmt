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
