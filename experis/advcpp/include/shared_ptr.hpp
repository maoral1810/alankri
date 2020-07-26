#ifndef SHARED_PTR_HPP_
#define SHARED_PTR_HPP_

#include "reference_count.hpp"
#include "releaser.hpp"

namespace advcpp {

template<class P>
class SharedPtr {

    template<class OTHER>
    friend class SharedPtr;

public:
    SharedPtr();
    explicit SharedPtr(P* a_ptr); // not allow conversion
    //~SharedPtr() = defualt;
    SharedPtr(const SharedPtr& a_other);
    SharedPtr& operator=(const SharedPtr& a_other);

    // copy & assigment conversion
    template<class OTHER>
    SharedPtr(const SharedPtr<OTHER>& a_ptr);
    template<class OTHER>
    SharedPtr<P>& operator=(const SharedPtr<OTHER>& a_ptr);

    P* operator->() const { return m_ptr; }
    P& operator*() const { return *m_ptr; }
    bool operator==(const SharedPtr& a_other) { return (m_ptr == a_other.m_ptr); }
    bool operator!=(const SharedPtr& a_other) { return !(this->operator == (a_other)); }
    P* GetPtr() const { return m_ptr; } 
    operator bool() const { return m_ptr != 0; } 

    void Foo() {/*for testing*/}
private:
    P* m_ptr;
    //Releaser<P> m_releaser;
    RefCount<Releaser<P> > m_refCount;
};


#include "shared_ptr_inl.hpp"

}//advcpp

#endif //SHARED_PTR_HPP_