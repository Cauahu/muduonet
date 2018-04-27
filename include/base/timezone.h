
/**
 * @file timezone.h
 * @author huzhuang
 * @date 2018/04/25
 * @brief this is a time zone, you can use tiemzone as a timeing point, and provides
 *        some motheds that convert struct tm to time_t and alse reseve.
 **/

#ifndef MUDUONET_BASE_TIMEZONE_H
#define MUDUONET_BASE_TIMEZONE_H

#include <memory>
#include <time.h>

namespace muduonet {

class TimeZone {
public:
    //explicit TimeZone(const char* zonefile);
    explicit TimeZone(time_t eastOfUtc);
    TimeZone();

    bool valid() const {
        //return static_cast<bool>(_data);
        return _iswork;
    }

    struct tm toLocalTime() const {
        return *localtime(&_utctime);
    }
    time_t fromLocalTime() const {
        return _utctime;
    }

    static struct tm toUtcTime(time_t utcseconds) {
        return *localtime(&utcseconds);
    }
    static time_t fromUtcTime(const struct tm& tm) {
        return mktime(&tm);
    }
    static time_t fromUtcTime(int year, int month, int day, int hour, int minute, int seconds) {
        struct tm t = {seconds, minute, hour, day, month, year};
        return fromUtcTime(&tm);
    }

    //struct Data;

private:
    //std::shared_ptr<Data> _data;
    bool _iswork;
    time_t _utctime;
}

}

#endif //MUDUONET_BASE_TIMEZONE_H
