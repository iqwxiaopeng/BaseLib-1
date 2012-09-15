#ifndef MUTEX_H_
#define MUTEX_H_
#include <boost/noncopyable.hpp>
#include <pthread.h>

namespace BaseLib
{
class Mutex:boost::noncopyable
{
public:
    Mutex()
    {
        pthread_mutex_init(&mutex_,NULL);
    }

    ~Mutex()
    {
        pthread_mutex_destroy(&mutex_);
    }

    void lock()
    {
        pthread_mutex_lock(&mutex_);
    }
    
    void unlock()
    {
        pthread_mutex_unlock(&mutex_);
    }

    void trylock()
    {
        pthread_mutex_trylock(&mutex_);
    }

    pthread_mutex_t* getMutex()
    {
        return &mutex_;
    }
private:
    pthread_mutex_t mutex_;
};

class MutexGuard:boost::noncopyable
{
public:
    explicit MutexGuard(Mutex& mutex):mtex_(mutex)
    {
        mtex_.lock();   
    }

    ~MutexGuard()
    {
        mtex_.unlock();
    }

private:
    Mutex& mtex_;
};
}
#endif
