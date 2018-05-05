
/**
 * @file logstream.h
 * @author huzhaung
 * @date 20180427
 * @brief this class implements a stream for log
 **/

#ifndef MUDUONET_BASE_LOGSTREAM_H
#define MUDUONET_BASE_LOGSTREAM_H

#include "base/stringpiece.h"
#include <string.h>
#include <string>

namespace muduonet {

const int kSmallBuffer = 4000;
const int kLargeBuffer = 4000 * 1000;

template<int SIZE>
class FixedBuffer {

public:
    FixedBuffer() : _cur(_data) {
    
    }

    ~FixedBuffer() {
    
    }
    
    const char* data() const { return _data; }
    
    int length() const {
        return static_cast<int>(_cur - _data);
    }

    char* current() { return _cur;}

    int avail() const { return static_cast<int>((_data + sizeof(_data)) - _cur); }

    void add(size_t len) { _cur += len; }

    void reset() { _cur = _data; }

    void bzero() { ::bzero(_data, sizeof(_data)); }

    void clear() { reset(); bzero(); }

    std::string toString() const {
        return std::string(_data, length());
    }

    StringPiece toStringPiece() const {
        return StringPiece(_data, length());
    }

    void append(const char* buf, size_t len) {
        if (static_cast<size_t>(avail()) > len) {
            memcpy(_cur, buf, len);
            _cur += len;
        }
    }

private:
    char _data[SIZE];
    char* _cur;
};

class LogStream {
public:
    typedef FixedBuffer<kSmallBuffer> Buffer;

    void append(const char* data, int len) {
        _buffer.append(data, len);
    }

    const Buffer& buffer() { return _buffer; }
    void resetBuffer() { _buffer.reset(); }

    LogStream& operator<<(bool v) {
        _buffer.append(v? "1":"0", 1);
        return *this;
    }

    LogStream& operator<<(short);
    LogStream& operator<<(unsigned short);
    LogStream& operator<<(int);
    LogStream& operator<<(unsigned int);
    LogStream& operator<<(long);
    LogStream& operator<<(unsigned long);
    LogStream& operator<<(long long);
    LogStream& operator<<(unsigned long long);
    LogStream& operator<<(double);
    LogStream& operator<<(const void*);

    LogStream& operator<<(float v) {
        *this << static_cast<double>(v);
        return *this;
    }

    LogStream& operator<<(char v) {
        _buffer.append(&v, 1);
        return *this;
    }

    LogStream& operator<<(const char* str) {
        if (NULL != str) {
            _buffer.append(str, strlen(str));
        } else {
            _buffer.append("(NULL)", 6);
        }
        return *this;
    }

    LogStream& operator<<(const std::string& str) {
        _buffer.append(str.c_str(), str.size());
        return *this;
    }

    LogStream& operator<<(const StringPiece& sp) {
        _buffer.append(sp.data(), sp.size());
        return *this;
    }

    LogStream& operator<<(const Buffer& v) {
        *this << v.toStringPiece();
        return *this;
    }

private:
    template<typename T>
    void formatInteger(T);

    Buffer _buffer;
    static const int kMaxNumericSize = 32;  //ensure that buffer can store a int type at least
};

class Fmt {
public:
    template<typename T>
    Fmt(const char* fmt, T val) {
        _length = snprintf(_buf, sizeof(_buf), fmt, val);
    }

    const char* data() const { return _buf; }
    int length() const { return _length; }

private:
    char _buf[32];
    int _length;
};

}

#endif //MUDUONET_BASE_LOGSTREAM_H
