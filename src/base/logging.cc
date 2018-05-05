#include "base/logging.h"
#include "base/timestamp.h"

#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sstream>

namespace muduonet {

    __thread char t_time[32];

    const char* LogLevelName[Logger::NUM_LOG_LEVELS] = {
        "TRACE",
        "DEBUG",
        "INFO",
        "WRAN",
        "ERROR",
        "FATAL",
    };

    class T {
    public :
        T(const char* str, int len) : _str(str), _len(len){

        }

        const char* _str;
        const int _len;
    };

    inline LogStream& operator<<(LogStream& s, T v) {
        s.append(v._str, v._len);
        return s;
    }

    inline LogStream& operator<<(LogStream& s, const Logger::SourceFile& v) {
        s.append(v._data, v._size);
        return s;
    }

    void defaultOutput(const char* msg, int len) {
        size_t n = fwrite(msg, 1, len, stdout);
        (void)n;
    }

    void defaultFlush() {
        fflush(stdout);
    }

    Logger::OutputFunc g_output = defaultOutput;
    Logger::FlushFunc g_flush = defaultFlush;
    Logger::LogLevel g_loglevel = Logger::INFO;

}

using namespace muduonet;

Logger::Impl::Impl(LogLevel level, int savedErrno, const SourceFile& file, int line) : _time(Timestamp::now()), _stream(), _level(level), _line(line), _basename(file){
    formatTime();
    _stream << static_cast<int>(getpid());
    _stream << T(LogLevelName[level], 6);
    if (savedErrno != 0) {
        _stream << strerror(savedErrno) << " [" << savedErrno << "]";
    }
}

void Logger::Impl::formatTime() {
    int64_t microSecondSinceEpoch = _time.microseconds();
    time_t seconds = static_cast<time_t>(microSecondSinceEpoch / Timestamp::kMicroSecondsPerSecond);
    int microseconds = static_cast<int>(microSecondSinceEpoch % Timestamp::kMicroSecondsPerSecond);

    struct tm tm_time;
    gmtime_r(&seconds, &tm_time);
    snprintf(t_time, sizeof(t_time), "%4d%02d%02d %02d:%02d:%02d", tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday, tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec);
    
    Fmt us(".%06d", microseconds);
    _stream << T(t_time, 17) << T(us.data(), 8);
}

void Logger::Impl::finish() {
    _stream << " - " << _basename << ":" << _line << '\n';
}

Logger::Logger(SourceFile file, int line) : _impl(INFO, 0, file, line) {

}

Logger::Logger(SourceFile file, int line, LogLevel level) : _impl(level, 0, file, line) {

}

Logger::Logger(SourceFile file, int line, LogLevel level, const char* func) : _impl(level, 0, file, line) {
    _impl._stream << func << ' ';
}

Logger::Logger(SourceFile file, int line, bool toAbort) : _impl(toAbort?FATAL:ERROR, errno, file, line) {

}

Logger::~Logger() {
    _impl.finish();
    const LogStream::Buffer& buf(stream().buffer());
    g_output(buf.data(), buf.length());
    g_flush();
    if (_impl._level == FATAL) {
        abort();
    }
}

void Logger::setLogLevel(Logger::LogLevel level) {
    g_loglevel = level;
}

Logger::LogLevel Logger::logLevel() {
    return g_loglevel;
}

void Logger::setOutput(OutputFunc out) {
    g_output = out;
}

void Logger::setFlush(FlushFunc flush) {
    g_flush = flush;
}

