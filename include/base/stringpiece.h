

/**
 * @fiel stringpiece.h
 * @author huzhuang
 * @date 20180426
 * @brief this is a string class like std::string
 **/

#ifndef MUDUONET_BASE_STRINGPIECE_H
#define MUDUONET_BASE_STRINGPIECE_H

#include <string.h>
#include <string>
#include <iostream>

namespace muduonet {

class StringArg {
public:
    StringArg(const char* str) : _str(str) {
    
    }

    StringArg(const std::string& str) : _str(str.c_str()) {
    
    }

    const char* c_str() const {
        return _str;
    }
private:
    const char* _str;
};

class StringPiece {
public:
    StringPiece() : _str(NULL), _length(0) {
    
    }

    StringPiece(const char* str) : _str(str), _length(static_cast<int>(strlen(str))) {
    
    }

    StringPiece(const std::string& str) : _str(str.data()), _length(static_cast<int>(str.size())) {
    
    }

    StringPiece(const char* offset, int len) : _str(offset), _length(len) {
    
    }

    StringPiece(const StringPiece& sp) : _str(sp._str), _length(sp._length){

    }

    StringPiece& operator=(const StringPiece& sp) {
        if(this == &sp) {
            return *this;
        }
        _str = sp._str;
        _length = sp._length;
        return *this;
    }

    const char* data() const {
        return _str;
    }

    int size() {
        return _length;
    }

    bool empty() {
        return 0 == _length;
    }

    const char* begin() {
        return _str;
    }

    const char* end() {
        return _str + _length;
    }

    void clear() {
        _str = NULL;
        _length = 0;
    }

    void set(const char* buffer, int len) {
        _str = buffer;
        _length = len;
    }

    void set(const char* buffer) {
        _str = buffer;
        _length = static_cast<int>(strlen(buffer));
    }

    void set(const void* buffer) {
        _str = reinterpret_cast<const char*>(buffer);
        _length = static_cast<int>(strlen(_str));
    }

    void remove_prefix(int n) {
        _str += n;
        _length -= n;
    }

    bool operator==(const StringPiece& sp) const {
        return (_length == sp._length) && (memcmp(_str, sp._str, _length) == 0);
    }

    bool operator!=(const StringPiece& sp) const {
        return !(*this == sp);    
    }

    bool operator<(const StringPiece& sp) const {
        int r = memcmp(_str, sp._str, _length < sp._length? _length : sp._length);
        return (r < 0) || ((r == 0) && (_length < sp._length));
    }
    
    bool operator<=(const StringPiece& sp) const {
        int r = memcmp(_str, sp._str, _length < sp._length? _length : sp._length);
        return (r < 0) || ((r == 0) && (_length <= sp._length));
    }

    bool operator>(const StringPiece& sp) const {
        int r = memcmp(_str, sp._str, _length < sp._length? _length : sp._length);
        return (r > 0) || ((r == 0) && (_length > sp._length));
    }

    bool operator>=(const StringPiece& sp) const {
        int r = memcmp(_str, sp._str, _length < sp._length? _length : sp._length);
        return (r > 0) || ((r == 0) && (_length >= sp._length));
    }

    int compare(const StringPiece& sp) {
        int r = memcmp(_str, sp._str, _length < sp._length? _length : sp._length);
        
        if (0 == r && _length < sp._length) {
            return -1;
        }
        
        if (0 == r && _length > sp._length) {
            return 1;
        }

        return 0;
    }

    std::string as_string() {
        return std::string(data(), size());
    }


private:
    const char* _str;
    int _length;
};

} //namespace muduonet

std::ostream& operator<<(std::ostream& o, const muduonet::StringPiece& sp) {
    o << sp.data();
    return o;
}

#endif //MUDUONET_BASE_STRINGPIECE_H
