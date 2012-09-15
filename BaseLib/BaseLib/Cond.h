#ifndef COND_H_
#define COND_H_

namespace BaseLib { 
class Cond : boost::noncopyable
{
public:
    Cond()
    {
        pthread_cond_init(&cond_,NULL);
    }

    ~Cond()
    {
        pthread_cond_destroy(&cond_);
    }

    void Wait()
    {
        pthread_cond_wait(&cond_,mutex_.GetMutex());  
    }

    void Signal()
    {
        pthread_cond_signal(&cond_);
    }   
  
    void Broadcast()
    {
        pthread_cond_broadcast(&cond_);
    }
private:
    Mutex& mutex_;
    pthread_cond_t cond_;
};
}//ACache
#endif
