#include "base/logstream.h"

#include <algorithm>
#include <limits>
#include <stdint.h>
#include <stdio.h>

using namespace muduonet;

const char digits[] = "9876543210123456789";
const char* zero = digits + 9;
const char digitsHex[] = "0123456789ABCDEF";

template<typename T>
size_t convert(char* buf, T value) {
    T i = value;
    char* p = buf;
    do {
        int lsd = static_cast<int>(i % 10);
        i /= 10;
        *p++ = zero[lsd];
    } while (i != 0);

    if (value < 0) {
        *p++ = '-';
    }
    *p = '\0';
    std::reverse(buf, p);

    return p - buf;
}

size_t convertHex(char* buf, uintptr_t value) {
    uintptr_t i = value;
    char*p = buf;

    do {
        int lsd = static_cast<int>(i % 16);
        i /= 16;
        *p++ = digitsHex[lsd];
    } while (i != 0);
    *p = '\0';
    std::reverse(buf, p);
    
    return p - buf;
}

template<typename T>
void LogStream::formatInteger(T v) {
    if (_buffer.avail() >= kMaxNumericSize) {
        size_t len = convert(_buffer.current(), v);
        _buffer.add(len);
    }
}

LogStream& LogStream::operator<<(short v) {
    *this << static_cast<int>(v);
    return *this;
}

LogStream& LogStream::operator<<(unsigned short v) {
    *this << static_cast<unsigned int>(v);
    return *this;
}

LogStream& LogStream::operator<<(int v) {
    formatInteger(v);
    return *this;
}

LogStream& LogStream::operator<<(unsigned int v) {
    formatInteger(v);
    return *this;
}

LogStream& LogStream::operator<<(long v) {
    formatInteger(v);
    return *this;
}

LogStream& LogStream::operator<<(unsigned long v) {
    formatInteger(v);
    return *this;
}

LogStream& LogStream::operator<<(long long v) {
    formatInteger(v);
    return *this;
}

LogStream& LogStream::operator<<(unsigned long long v) {
    formatInteger(v);
    return *this;
}

LogStream& LogStream::operator<<(double v) {
    if (_buffer.avail() >= kMaxNumericSize) {
        int len = snprintf(_buffer.current(), kMaxNumericSize, "%.12g", v);
        _buffer.add(len);
    }
    return *this;
}

LogStream& LogStream::operator<<(const void* p) {
    if (_buffer.avail() >= kMaxNumericSize) {
        int len = snprintf(_buffer.current(), kMaxNumericSize, "%p", p);
        _buffer.add(len);
    }
    return *this;
}

inline LogStream& operator<<(LogStream& s, const Fmt& fmt) {
    s.append(fmt.data(), fmt.length());
    return s;
}

/*
template<typename T>
Fmt::Fmt(const char* fmt, T val) {
    _length = snprintf(_buf, sizeof(_buf), fmt, val);
}
//explicit instantiations
template Fmt::Fmt(const char* fmt,char);
template Fmt::Fmt(const char* fmt, short);
template Fmt::Fmt(const char* fmt, unsigned short);
template Fmt::Fmt(const char* fmt, int);
template Fmt::Fmt(const char* fmt, unsigned int);
template Fmt::Fmt(const char* fmt, long);
template Fmt::Fmt(const char* fmt, unsigned long);
template Fmt::Fmt(const char* fmt, long long);
template Fmt::Fmt(const char* fmt, unsigned long long);
template Fmt::Fmt(const char* fmt, );
template Fmt::Fmt(const char* fmt, );*/
