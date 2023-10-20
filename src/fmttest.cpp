#include <Arduino.h>
#include <Fmt.h>
#include <fmt/color.h>
#include <fmt/ranges.h>
#include <vector>

Fmt f(&Serial);
// Fmt f(Serial); // works too

// fmtlib library panic handler
extern "C" {
void fmtlib_error(const char *file, int line, const char *message) {
  Serial.printf("%s:%d: assertion failed: %s\n", file, line, message);
}
}

void setup() {
  delay(3000);
  Serial.begin(115200);
  while (!Serial) {
    yield();
  }
  // see also:
  // https://github.com/fmtlib/fmt
  // https://fmt.dev/latest/syntax.html#format-specification-mini-language

  std::string s = fmt::format("The answer is {}.", 42);
  s = fmt::format("The answer is {}.", 42);

  f.fmt("{}{}\n", "foo", 4711);
  f.fmtln("with implicit newline {}{}", "bar", 815);

  std::vector<int> v = {1, 2, 3};
  fmt::print("{}\n", v);

  fmt::print(fg(fmt::color::crimson) | fmt::emphasis::bold, "Hello, {}!\n",
             "world");
  fmt::print(fg(fmt::color::floral_white) | bg(fmt::color::slate_gray) |
                 fmt::emphasis::underline,
             "Hello, {}!\n", "мир");
  fmt::print(fg(fmt::color::steel_blue) | fmt::emphasis::italic, "Hello, {}!\n",
             "世界");
}

void loop() { yield(); }
