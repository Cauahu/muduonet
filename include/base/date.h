
/**
 * @file date.h
 * @author huzhuang
 * @date 20180521
 * @brief this class is used to present calendar
 **/

#ifndef MUDUONET_BASE_DATE
#define MUDUONET_BASE_DATE

#include <time.h>
#include <string>

namespace muduonet{

class Date {
public:
    struct YearMonthDay {
        int year; //[1900...2500]
        int month; //[1...12]
        int day; //[1...31]
    };

    static const int kDaysPerWeek = 7;
    static const int kJulianDayof19700101;

    Date() : _julianDayNumber(0) {
    
    }

    Date(int year, int month, int day);

    explicit Date(int julianDayNum) : _julianDayNumber(julianDayNum) {
    
    }

    explicit Date(const struct tm&);

    void swap(Date& that) {
        std::swap(_julianDayNumber, that._julianDayNumber);
    }

    bool valid() const {
        return _julianDayNumber > 0;
    }

    std::string toString() const;

    struct YearMonthDay yearMonthDay() const;

    int year() const {
        return yearMonthDay().year;
    }

    int month() const {
        return yearMonthDay().month;
    }

    int day() const {
        return yearMonthDay().day;
    }

    int weekDay() const {
        return (_julianDayNumber + 1) % kDaysPerWeek;
    }

    int julianDayNumber() const {
        return _julianDayNumber;
    }

private:
    int _julianDayNumber;
};

inline bool operator<(Date lhs, Date rhs) {
    return lhs.julianDayNumber() < rhs.julianDayNumber();
}

inline bool operator==(Date lhs, Date rhs) {
    return lhs.julianDayNumber() == rhs.julianDayNumber();
}

inline bool operator>(Date lhs, Date rhs) {
    return lhs.julianDayNumber() > rhs.julianDayNumber();
}

}

#endif //MUDUONET_BASE_DATE
