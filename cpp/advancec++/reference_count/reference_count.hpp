#ifndef REFERENCE_COUNT_HPP_
#define REFERENCE_COUNT_HPP_

#include <signal.h> // sig_atomic_t
#include <stdio.h>  // sig_atomic_t

#include <cstddef>          // size_t

namespace experis {
template<class FUNCTOR>
class RefCount {

    typedef sig_atomic_t COUNTER_TYPE; // volatile for not optimized??
    
    template <class OTHER>
    friend class RefCount;
public:
    explicit RefCount(FUNCTOR a_deleteFunc);
    template<class OTHER>
    RefCount(const RefCount<OTHER>& a_other);
    ~RefCount();
    RefCount(const RefCount& a_other); // cctor
    RefCount& operator=(const RefCount& a_other);

    COUNTER_TYPE* Get() const { return m_counter; }
    RefCount& operator++(); 
    COUNTER_TYPE operator*() { return *m_counter; }
    operator bool(){ return (*m_counter) != 0; }
    
private:
    COUNTER_TYPE* increaceRefCount(COUNTER_TYPE* a_other);
    void decreaseAndTerminate();

    COUNTER_TYPE* m_counter;
    FUNCTOR m_deleteFunc;
};

#include "reference_count_inl.hpp"
}//experis

#endif // REFERENCE_COUNT_HPP_

