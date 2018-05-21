
/**
 * @file logfile.h
 * @author huzhuang
 * @date 20180506
 * @brief this class is used to store log, and provide roolling logfile according to rollsize.
 */

#ifndef MUDUO_BASE_LOGFILE_H
#define MUDUO_BASE_LOGFILE_H

#include <memory>
#include <string>
#include "base/mutex.h"

namespace muduonet {
    
namespace fileutil {
  class AppendFile;
}

class LogFile {
public:
    LogFile(const std::string& basename, off_t rollSize, bool threadSafe = true, int flushInterval = 3, int checkEveryN = 1024);
    ~LogFile();

    void append(const char* logline, int len);
    void flush();
    bool rollfile();

private:
    void append_unlocked(const char* logline, int len);
    static std::string getLogFileName(const std::string& basename, time_t now);

    const std::string _basename;
    const off_t _rollSize;
    const int _flushInterval;
    const int _checkEveryN;

    //cout is used to compare with checkEveryN, when lager than checkEveryN,roll log file
    int _count;

    std::unique_ptr<Mutex> _mutex;
    time_t _startOfPeriod; //roll log file timing, if time is not equal it roll file
    time_t _lastRoll;
    time_t _lastFlush;
    std::unique_ptr<fileutil::AppendFile> _file;
    const static int _kRollPerSeconds = 60*60*24;
};

}

#endif //MUDUO_BASE_LOGFILE_H
