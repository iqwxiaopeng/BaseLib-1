#ifndef BASE_THREAD_H
#define BASE_THREAD_H
#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include "Atomic.h"
#include <pthread.h>
#include <string>
using namespace std;
namespace ACache{
class Thread: boost::noncopyable
{
public:
    typedef boost::function<void ()> ThreadFunc;
    explicit Thread(const ThreadFunc&, const string& name = string());
    ~Thread();
    
    void start();
    void join();

    bool started() const
    {
        return startedM;   
    }

    bool running() const
    {
        return runningM;
    }

    bool detachable() const
    {
        return detachableM; 
    }

    pid_t pid()
    {
        return pidM;
    }

    const string& name()
    {
        return nameM;
    }

    static int totalThrd() 
    {
        return totalThrdM.fetch();
    }

private:
    static atomic_int  totalThrdM;
    static void *startThread(void* thread);
    void run();

    bool startedM;    
    bool runningM;   
    bool detachableM;

    pthread_t  thrdIdM;
    pid_t pidM;
    ThreadFunc funcM;
    string nameM;
};

namespace CurrentThread
{
    pid_t tid();

    const char *name();

    bool isMainThread();
}

}//multiThread
#endif
