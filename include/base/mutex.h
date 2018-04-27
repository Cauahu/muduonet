
/**
 * @file mutex.h
 * @author huzhuang
 * @date 20180425
 * @brief custom a mutex lock
 **/

#ifndef MUDUONET_BASE_MUTEX_H
#define MUDUONET_BASE_MUTEX_H

#include <assert.h>
#include <pthread.h>

namespace muduonet {

class Mutex {

public:
    Mutex() : _holder(0) {
        pthread_mutex_init(&_mutex, NULL);
    }

    ~Mutex() {
        if (_holder == 0) {
            pthread_mutex_destroy(&_mutex); 
        }
    }

    bool isLockedByThisThread() const {
        return _holder == pthread_self();
    }

    void assertLocked() const {
        assert(isLockedByThisThread());
    }

    void lock() {
        pthread_mutex_lock(&_mutex);
        assignHolder();
    }

    void unlock() {
        unassignHolder();
        pthread_mutex_unlock(&_mutex);
    }

    pthread_mutex_t* getMutex() {
        return &_mutex;
    }

private:
    friend class Condition;
    
    class Unassignguard {
    public:
        Unassignguard(Mutex& owner) : _owner(owner) {
            _owner.unassignHolder();
        }

        ~Unassignguard() {
            _owner.assignHolder();
        }
    private:
        Mutex& _owner;
    };

    void unassignHolder() {
        _holder = 0;
    }

    void assignHolder() {
        _holder = pthread_self();
    }
    
    pthread_mutex_t _mutex;
    pthread_t _holder;

};

class MutexGuard {
public:
    explicit MutexGuard(Mutex& mutex) : _mutex(mutex) {
        _mutex.lock();
    }

    ~MutexGuard() {
        _mutex.unlock();
    }

private:
    Mutex& _mutex;
};

}

#endif //MUDUONET_BASE_MUTEX_H
