
/**
 * @file logging.h
 * @author huzhuang
 * @date 2018/05/02
 * @brief implement for logging
 **/

#ifndef MUDUONET_BASE_LOGGING_H
#define MUDUONET_BASE_LOGGING_H

#include "base/logstream.h"
#include "base/timestamp.h"

namespace muduonet {

class Logger {
public:
    enum LogLevel {
        TRACE,
        DEBUG,
        INFO,
        WARN,
        ERROR,
        FATAL,
        NUM_LOG_LEVELS,
    };

    class SourceFile {
    public:
        SourceFile(const char* filename) : _data(filename) {
            /*
            const char* slash = strrchr(_data, '/');
            if (slash) {
                _data = slash + 1;
            }
            */
            _size = static_cast<int>(strlen(_data));
        }

        const char* _data;
        int _size;
    };

    Logger(SourceFile file, int line);
    Logger(SourceFile file, int line, LogLevel level);
    Logger(SourceFile file, int line, LogLevel level, const char* func);
    Logger(SourceFile file, int line, bool toAbort);
    ~Logger();

    LogStream& stream() {
        return _impl._stream;
    }

    static LogLevel logLevel();
    static void setLogLevel(LogLevel level);

    typedef void (*OutputFunc)(const char* msg, int len);
    typedef void (*FlushFunc)();

    static void setOutput(OutputFunc);
    static void setFlush(FlushFunc);

private:

    class Impl {
    public:
        typedef Logger::LogLevel LogLevel;
        Impl(LogLevel level, int old_errno, const SourceFile& file, int line);
        void formatTime();
        void finish();

        Timestamp _time;
        LogStream _stream;
        LogLevel _level;
        int _line;
        SourceFile _basename;
    };

    Impl _impl;

};

}

#define LOG_TRACE if (muduonet::Logger::logLevel() <= muduonet::Logger::TRACE) \
                                                      muduonet::Logger(__FILE__, __LINE__, muduonet::Logger::TRACE, __func__).stream()

#define LOG_DEBUG if (muduonet::Logger::logLevel() <= muduonet::Logger::DEBUG) \
                                                      muduonet::Logger(__FILE__, __LINE__, muduonet::Logger::DEBUG, __func__).stream()

#define LOG_INFO if (muduonet::Logger::logLevel() <= muduonet::Logger::INFO) \
                                                      muduonet::Logger(__FILE__, __LINE__, muduonet::Logger::INFO, __func__).stream()

#define LOG_WARN muduonet::Logger(__FILE__, __LINE__, muduonet::Logger::WARN, __func__).stream()

#define LOG_ERROR muduonet::Logger(__FILE__, __LINE__, muduonet::Logger::ERROR, __func__).stream()

#define LOG_FATAL muduonet::Logger(__FILE__, __LINE__, muduonet::Logger::FATAL, __func__).stream()

#define LOG_SYSERR muduonet::Logger(__FILE__, __LINE__, false).stream()

#define LOG_SYSFATAL muduonet::Logger(__FILE__, __LINE__, true).stream()

#endif //MUDUONET_BASE_LOGGING_H
