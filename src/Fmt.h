#pragma once

#include <Stream.h>
#undef B1
#undef F
#ifndef FMT_NODISCARD
#define FMT_NODISCARD
#endif
#include <StreamUtils.h>
#include <fmt/core.h>
#include <fmt/format.h>

using namespace fmt;

class Fmt : public Stream {

public:
  Fmt(Stream &stream, String eol = "\n") : eol_(eol), stream_(&stream){};
  Fmt(Stream *stream, String eol = "\n") : eol_(eol), stream_(stream){};
  Fmt(String eol = "\n") : eol_(eol) {
    stream_ = new StringStream();
    allocated_ = true;
  };
  ~Fmt() {
    if (allocated_) {
      delete stream_;
    }
  }
  template <typename... T>
  FMT_NODISCARD FMT_INLINE int fmt(format_string<T...> fmt, T &&...args) {
    std::string s = vformat(fmt, fmt::make_format_args(args...));
    return write((const uint8_t *)s.c_str(), s.length());
  }

  template <typename... T>
  FMT_NODISCARD FMT_INLINE int fmtln(format_string<T...> fmt, T &&...args) {
    std::string s = vformat(fmt, fmt::make_format_args(args...));
    auto l = write((const uint8_t *)s.c_str(), s.length());
    l += write((const uint8_t *)eol_.c_str(), eol_.length());
    return l;
  }

  size_t write(uint8_t c) { return stream_->write(c); };

  size_t write(const uint8_t *buffer, size_t size) {
    return stream_->write(buffer, size);
  };
  int available() { return 0; };
  int read() { return 0; };
  int peek() { return 0; };

  Stream &stream(void) {return *stream_;};

private:
  // const std::locale &locale_ = std::locale("en_US.UTF-8");
  String eol_;
  Stream *stream_;
  bool allocated_;
};
