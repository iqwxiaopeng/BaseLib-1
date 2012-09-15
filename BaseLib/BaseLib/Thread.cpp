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

    pid_t Gettid()
    {
        return static_cast<pid_t>(::syscall(__NR_gettid));
    }

    void AfterFork()
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

using namespace BaseLib;
using namespace BaseLib::detail;

pid_t CurrentThread::Tid()
{
    if(t_tid == 0)
    {
        t_tid = gettid();
    }
    return t_tid;
}

const char* CurrentThread::Name()
{
    return t_name;
}

bool CurrentThread::IsMainThread()
{
    return tid() == ::getpid();
}

atomic_int Thread::TotalThrd_;

Thread::Thread(const ThreadFunc& func, const string& n)
:started_(false),
 thrdId_(0),
 pid_(0),
 func_(func),
 name_(n)
{
}

void Thread::Start()
{
    assert(!started_);
    started_ = true;
    pthread_create(&thrdId_, NULL,&StartThread, this);
}

void Thread::Join()
{
    assert(started_);
    pthread_join(thrdId_,NULL);   
}

void* Thread::StartThread(void *arg)
{
    Thread* thread = static_cast<Thread*>(arg);
    thread->run();
    return NULL;    
}

void Thread::Run()
{
    pid_ = CurrentThread::tid();
    BaseLib::CurrentThread::t_name = name_.c_str();
    func_();
    BaseLib::CurrentThread::t_name = "finished";
}


