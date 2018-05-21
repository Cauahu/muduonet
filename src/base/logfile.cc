
#include "base/logfile.h"
#include "base/fileutil.h"

#include <stdio.h>
#include <time.h>

using namespace muduonet;

LogFile::LogFile(const std::string& basename, off_t rollSize, bool threadSafe, int flushInterval, int checkEveryN) : _basename(basename), _rollSize(rollSize), _flushInterval(flushInterval), _checkEveryN(checkEveryN), _count(0), _mutex(threadSafe ? new Mutex : NULL), _startOfPeriod(0), _lastRoll(0), _lastFlush(0) {
    assert(basename.find('/') == std::string::npos);
    rollfile();
}

LogFile::~LogFile() {

}

void LogFile::append(const char* logline, int len) {
    if (_mutex) {
        MutexGuard lock(*_mutex);
        append_unlocked(logline, len);
    } else {
        append_unlocked(logline, len);
    }
}

void LogFile::flush() {
    if (_mutex) {
        MutexGuard lock(*_mutex);
        _file->flush();
    } else {
        _file->flush();
    }
}

void LogFile::append_unlocked(const char* logline, int len) {
    _file->append(logline, len);
    if (_file->writtenBytes() > _rollSize) {
        rollfile();
    } else {
        ++_count;
        if (_count >= _checkEveryN) {
            _count = 0;
            time_t now = ::time(NULL);
            time_t thisPeriod = now / _kRollPerSeconds * _kRollPerSeconds;
            if (thisPeriod != _startOfPeriod) {
                rollfile();
            } else if (now - _lastFlush > _flushInterval) {
                _lastFlush = now;
                _file->flush();
            }
        }
    }
}

bool LogFile::rollfile() {
    time_t now = time(NULL);
    std::string filename = getLogFileName(_basename, now);
    
    if (now > _lastRoll) {
        _lastRoll = now;
        _lastFlush = now;
        _startOfPeriod = now / _kRollPerSeconds * _kRollPerSeconds;
        _file.reset(new fileutil::AppendFile(filename.c_str()));
        return true;
    }
    return false;
}

std::string LogFile::getLogFileName(const std::string& basename, time_t now) {
    std::string filename(basename);
    filename.reserve(filename.size() + 64);

    char buf[32];
    struct tm tm;
    localtime_r(&now, &tm);
    strftime(buf, 32, ".%Y%m%d-%H%M%S.", &tm);

    filename += buf;
    filename += "log";
    
    return filename;
}
