#ifndef RELEASER_HPP_
#define RELEASER_HPP_

namespace advcpp {

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

#include "inl/releaser_inl.hpp"

}// advcpp

#endif //RELEASER_HPP_