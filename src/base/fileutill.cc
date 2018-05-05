#include "base/fileutill.h"

#include "assert.h"

using namespace muduonet;

using namespace muduonet::FileUtil;

AppendFile::AppendFile(const char* filename) :  _writtenBytes(0) {
    _fp = ::fopen(filename, "ae");
    assert(_fp);
    ::setbuffer(_fp, _buffer, kBufferSize);
}

AppendFile::~AppendFile() {
    fclose(_fp);
}

//@return actually write into file's bytes
size_t AppendFile::append(const char* logline, const size_t len) {
    size_t remain = len, n = 0;
    do {
        size_t x = ::fwrite(logline + n, 1, remain, _fp);
        if (x == 0) {
            int err = ferror(_fp);
            if (err) {
                fprintf(stderr, "AppendFile::append() failed %s\n", strerror(err));
            }
            break;
        }
        n += x;
        remain -= x;
    } while (remain > 0);
    _writtenBytes += n;
    return n;
}

void AppendFile::flush() {
    ::fflush(_fp);
}

ReadFile::ReadFile(const char* filename) : _err(0) {
    _fd = ::open(filename, O_RDONLY | O_CLOEXEC);
    _buf[0] = '\0';
    if (_fd < 0) {
        _err = errno;
    }
}

ReadFile::~ReadFile() {
    if (_fd >= 0) {
        ::close(_fd);
    }
}
