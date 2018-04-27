
/**
 * @file timestamp.h
 * @author huzhuang
 * @date 2018/04/25
 * @brief provide a microsecond time stamp
 **/

#ifndef MUDUONET_BASE_TIMESTAMP_H
#define MUDUONET_BASE_TIMESTAMP_H

#include <string>

namespace muduonet {

class Timestamp {
public:
    Timestamp() : _microseconds(0) {
    
    }

    explicit Timestamp(int64_t microseconds) : _microseconds(microseconds){
    
    }

    void swap(Timestamp& that) {
        std::swap(_microseconds, that._microseconds);
    }

    std::string toString() const;
    std::string toFormattedString(bool showmicroseconds) const;

    bool valid() const {
        return _microseconds > 0;
    }

    int64_t microseconds() const { return _microseconds;}
    time_t seconds() const {
        return static_cast<time_t>(_microseconds / kMicroSecondsPerSecond);
    }

    static Timestamp now();

    static Timestamp fromUnixTime(time_t t) {
        return fromUnixTime(t, 0);
    }

    static Timestamp fromUnixTime(time_t t, int microseconds) {
        return Timestamp(static_cast<int64_t>(t) * kMicroSecondsPerSecond + microseconds);
    }

    static const int kMicroSecondsPerSecond = 1000 * 1000;
    
    
private:
    int64_t _microseconds;

};

//lhs = left hand side, rhs = right hand side
inline bool operator<(Timestamp lhs, Timestamp rhs) {
    return lhs.microseconds() < rhs.microseconds();
}

inline bool operator==(Timestamp lhs, Timestamp rhs) {
    return lhs.microseconds() == rhs.microseconds();
}

inline double timeDiff(Timestamp lhs, Timestamp rhs) {
    int64_t diff = lhs.microseconds() - rhs.microseconds();
    return static_cast<double>(diff) / Timestamp::kMicroSecondsPerSecond;
}

inline Timestamp addTime(Timestamp timestamp, double seconds) {
    int64_t delta = static_cast<int64_t>(seconds * Timestamp::kMicroSecondsPerSecond);
    return Timestamp(timestamp.microseconds() + delta);
}

}
#endif //MUDUONET_BASE_TIMESTAMP_H
