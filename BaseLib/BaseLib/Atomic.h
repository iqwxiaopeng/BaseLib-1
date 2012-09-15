#ifndef ATOMIC_H_
#define ATOMIC_H_
#include <stdint.h>
namespace BaseLib 
{
template <typename T>
class Atomic:boost::noncopyable 
{
public:
    Atomic():value_(0)
    {
    }

    T fetch()
    {
        return __sync_val_compare_and_swap(&value_,0,0); 
    }

    T fetchAndAdd(T x)
    {
        return __sync_fetch_and_add(&value_, x);  
    }
private:
    volatile T value_;
};

typedef Atomic<int> atomic_int;
}
#endif
