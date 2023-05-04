#pragma once

#include <Stream.h>
#undef B1
#include <fmt/core.h>
#include <fmt/format.h>
using namespace fmt;

class Fmt : public Stream {

public:
  Fmt(Stream &stream) : stream_(&stream){};
  Fmt(Stream *stream) : stream_(stream){};

  template <typename... T>
  FMT_NODISCARD FMT_INLINE int fmt(format_string<T...> fmt, T &&...args) {
    std::string s = vformat(fmt, fmt::make_format_args(args...));
    return write((const uint8_t *)s.c_str(), s.length());
  }

  size_t write(uint8_t c) { return stream_->write(c); };

  size_t write(const uint8_t *buffer, size_t size) {
    return stream_->write(buffer, size);
  };
  int available() { return 0; };
  int read() { return 0; };
  int peek() { return 0; };

private:
  Stream *stream_;
};
