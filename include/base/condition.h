
/**
 * @file condition.h
 * @author huzhuang
 * @date 20180425
 * @brief this is a condition
 **/

#ifndef MUDUONET_BASE_CONDITION_H
#define MUDUONET_BASE_CONDITION_H


#include "base/mutex.h"
#include <pthread.h>
#include <errno.h>
#include <time.h>

namespace muduonet {

class Condition{
public:
    explicit Condition(Mutex& mutex) : _mutex(mutex) {
        pthread_cond_init(&_pcond, NULL);
    }

    ~Condition() {
        pthread_cond_destroy(&_pcond);
    }

    void wait() {
        Mutex::Unassignguard ug(_mutex);
        pthread_cond_wait(&_pcond, _mutex.getMutex());
    }

    bool waitforseconds(double seconds) {
        struct timespec abstime;
        clock_gettime(CLOCK_REALTIME, &abstime);
    
        const int64_t kNanoSecondsPerSecond = 100000000;
        int64_t nanoseconds = static_cast<int64_t>(seconds * kNanoSecondsPerSecond);

        abstime.tv_sec += static_cast<time_t>((abstime.tv_nsec + nanoseconds) / kNanoSecondsPerSecond);
        abstime.tv_nsec = static_cast<long>((abstime.tv_nsec + nanoseconds) % kNanoSecondsPerSecond);

        Mutex::Unassignguard ug(_mutex);
        return ETIMEDOUT == pthread_cond_timedwait(&_pcond, _mutex.getMutex(), &abstime);
    }
    
    void notify() {
        pthread_cond_signal(&_pcond);
    }

    void notifyAll() {
        pthread_cond_broadcast(&_pcond);
    }

private:
    Mutex& _mutex;
    pthread_cond_t _pcond;
};

}


#endif //MUDUONET_BASE_CONDITION_H
