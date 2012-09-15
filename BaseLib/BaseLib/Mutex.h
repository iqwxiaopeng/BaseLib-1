#ifndef MUTEX_H_
#define MUTEX_H_
#include <boost/noncopyable.hpp>
#include <pthread.h>

namespace ACache
{
class Mutex:boost::noncopyable
{
public:
    Mutex()
    {
        pthread_mutex_init(&mutexM,NULL);
    }

    ~Mutex()
    {
        pthread_mutex_destroy(&mutexM);
    }

    void lock()
    {
        pthread_mutex_lock(&mutexM);
    }
    
    void unlock()
    {
        pthread_mutex_unlock(&mutexM);
    }

    void trylock()
    {
        pthread_mutex_trylock(&mutexM);
    }

    pthread_mutex_t* getMutex()
    {
        return &mutexM;
    }
private:
    pthread_mutex_t mutexM;
};

class MutexGuard:boost::noncopyable
{
public:
    explicit MutexGuard(Mutex& mutex):mtexM(mutex)
    {
        mtexM.lock();   
    }

    ~MutexGuard()
    {
        mtexM.unlock();
    }

private:
    Mutex& mtexM;
};
}
#endif
