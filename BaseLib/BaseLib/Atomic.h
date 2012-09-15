#ifndef ATOMIC_H_
#define ATOMIC_H_
#include <stdint.h>
template <typename T>
class Atomic:boost::noncopyable 
{
public:
    Atomic()
    :valueM(0)
    {

    }

    T fetch()
    {
        return __sync_val_compare_and_swap(&valueM,0,0); 
    }

    T fetchAndAdd(T x)
    {
        return __sync_fetch_and_add(&valueM,x);  
    }
private:
    volatile T valueM;
};

typedef Atomic<int> atomic_int;
#endif
