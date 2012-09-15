#ifndef COND_H_
#define COND_H_

namespace ACache { 
class Cond : boost::noncopyable
{
public:
    Cond()
    {
        pthread_cond_init(&condM,NULL);
    }

    ~Cond()
    {
        pthread_cond_destroy(&condM);
    }

    void wait()
    {
        pthread_cond_wait(&condM,mutexM.getMutex());  
    }

    void signal()
    {
        pthread_cond_signal(&condM);
    }   
  
    void broadcast()
    {
        pthread_cond_broadcast(&condM);
    }
private:
    Mutex& mutexM;
    pthread_cond_t condM;
};
}//ACache
#endif
