
/**
 * @file fileutill.h
 * @author huzhuang
 * @date 20180505
 * @brief an utill that provide simple file operation like open/close、append、flush ec, a kind of RAII.
 **/

#ifndef MUDUONET_BASE_FILEUTILL_H
#define MUDUONET_BASE_FILEUTILL_H

#include "base/stringpiece.h"
#include "errno.h"
#include "fcntl.h"
#include "stdio.h"
#include "sys/stat.h"
#include "unistd.h"


namespace muduonet {

namespace FileUtil {

static const int kBufferSize = 64*1024;

class AppendFile {
public:
    explicit AppendFile(const char* filename);
    
    ~AppendFile();

    size_t append(const char* logline, const size_t len);

    void flush();

    off_t writtenBytes() const {
        return _writtenBytes;
    }
    
private:

    FILE* _fp;
    char _buffer[kBufferSize];
    off_t _writtenBytes;
};

class ReadFile {
public:
    explicit ReadFile(const char* filename);
    ~ReadFile();

    template<typename T>
    int readToString(int maxSize, T* content, int64_t* fileSize, int64_t* modifyTime, int64_t* createTime);

    int readToBuffer(int* size);

    const char* buffer() const {
        return _buf;
    }
    
private:
    int _fd;
    int _err;
    char _buf[kBufferSize];
};

//@return errno
template<typename T>
int ReadFile::readToString(int maxSize, T* content, int64_t* fileSize, int64_t* modifyTime, int64_t* createTime) {
    int err =  _err;
    if (_fd < 0 || !fileSize) {
        return err;
    }

    content->clear();

    struct stat statbuf;
    if (::fstat(_fd, &statbuf) != 0) {
        return errno;
    }

    if (S_ISREG(statbuf.st_mode)) {
        *fileSize = statbuf.st_size;
        content->reserve(static_cast<int>(std::min(static_cast<int64_t>(maxSize), *fileSize)));
    } else if (S_ISDIR(statbuf.st_mode)) {
        return EISDIR;        
    }
    if (modifyTime) {
        *modifyTime = statbuf.st_mtime;
    }
    if (createTime) {
        *createTime = statbuf.st_ctime;
    }

    while (content->size() < maxSize) {
        size_t toRead = std::min(static_cast<size_t>(maxSize) - content->size(), kBufferSize);
        ssize_t n = ::read(_fd, _buf, toRead);
        if (n > 0) {
            content->append(_buf, n);
        } else {
            err = n < 0? errno : _err;
            break;
        }
    }
    return err;
}

int ReadFile::readToBuffer(int* size) {
    int err = _err;
    if (_fd < 0) {
        return err;
    }

    ssize_t n = ::pread(_fd, _buf, kBufferSize - 1, 0);
    if (n >= 0) {
        _buf[n] = '\0';
        if (size) {
            *size = static_cast<int>(n);
        }
    } else {
        err = errno;
    }
    return err;
}

template<typename T>
int readFile(const char* filename, int maxSize, T* content, int64_t* fileSize = NULL, int64_t modifyTime = NULL, int64_t createTime = NULL) {
    ReadFile file(filename);
    return file.readToString(maxSize, content, fileSize, modifyTime, createTime);
}

}

}


#endif //MUDUONET_BASE_FILEUTILL_H
