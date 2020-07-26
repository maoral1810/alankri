#ifndef SINGLE_PTR_HPP_
#define SINGLE_PTR_HPP_

#include "uncopyable.hpp"

namespace experis{

template<class T>
class SinglePtr : private Uncopyable {
public:
    SinglePtr(T* a_ptr);
    ~SinglePtr();
    T& operator*() const { return *m_ptr; }
    T* operator->() const { return m_ptr; }

private:
    T* m_ptr;
};

template<class T>
SinglePtr<T>::SinglePtr(T* a_ptr)
    : m_ptr(a_ptr)
{

}

template<class T>
SinglePtr<T>::~SinglePtr() {
    delete m_ptr;
}


}// experis

#endif //SINGLE_PTR_HPP_