#ifndef RELEASER_HPP_
#define RELEASER_HPP_

namespace experis {

template<class P>
class Releaser {
    template<class OTHER>
    friend class Releaser;

public:
    Releaser(P* a_ptr);
    void operator()();

    template<class OTHER>
    Releaser(const Releaser<OTHER>& a_other);
private:
    P* m_toRelese;
};

#include "releaser_inl.hpp"

}// experis

#endif //RELEASER_HPP_