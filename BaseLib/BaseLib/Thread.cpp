#include "Thread.h"
#include <sys/syscall.h>
#include <sys/types.h>
#include <linux/unistd.h>
#include <unistd.h>

namespace ACache{

namespace CurrentThread 
{
    __thread const char* t_name = "unknown";
}

namespace detail
{
    __thread pid_t t_tid = 0;

    pid_t gettid()
    {
        return static_cast<pid_t>(::syscall(__NR_gettid));
    }

    void afterFork()
    {
        t_tid = gettid();
        ACache::CurrentThread::t_name = "main";
    }

    class ThreadNameInitializer
    {
        public:
            ThreadNameInitializer()
            {
                ACache::CurrentThread::t_name = "main";
                pthread_atfork(NULL,NULL,&afterFork);
            }  
    };

    ThreadNameInitializer init;
}
}//multiThread

using namespace ACache;
using namespace ACache::detail;

pid_t CurrentThread::tid()
{
    if(t_tid == 0)
    {
        t_tid = gettid();
    }
    return t_tid;
}

const char* CurrentThread::name()
{
    return t_name;
}

bool CurrentThread::isMainThread()
{
    return tid() == ::getpid();
}

atomic_int Thread::totalThrdM;

Thread::Thread(const ThreadFunc& func, const string& n)
:startedM(false),
 thrdIdM(0),
 pidM(0),
 funcM(func),
 nameM(n)
{
}

void Thread::start()
{
    assert(!startedM);
    startedM = true;
    pthread_create(&thrdIdM, NULL,&startThread, this);
}

void Thread::join()
{
    assert(startedM);
    pthread_join(thrdIdM,NULL);   
}

void* Thread::startThread(void *arg)
{
    Thread* thread = static_cast<Thread*>(arg);
    thread->run();
    return NULL;    
}

void Thread::run()
{
    pidM = CurrentThread::tid();
    ACache::CurrentThread::t_name = nameM.c_str();
    funcM();
    ACache::CurrentThread::t_name = "finished";
}


