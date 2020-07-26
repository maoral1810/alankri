#ifndef RELEASER_INL_HPP_
#define RELEASER_INL_HPP_

template<class P>
Releaser<P>::Releaser(P* a_ptr)
    : m_toRelese(a_ptr)
{

}

template<class P>
void Releaser<P>::operator()() {
    delete m_toRelese; 
}

template<class P>
template<class OTHER>
Releaser<P>::Releaser(const Releaser<OTHER>& a_other)
    : m_toRelese(static_cast<P*>(a_other.m_toRelese))
{

}


#endif // RELEASER_INL_HPP_
