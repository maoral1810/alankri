
template<class P>
SharedPtr<P>::SharedPtr()
    : m_ptr(0)
    //, m_releaser(m_ptr)
    , m_refCount(Releaser<P>(m_ptr)) 
{

}

template<class P>
SharedPtr<P>::SharedPtr(P* a_ptr)
    : m_ptr(a_ptr)
    //, m_releaser(m_ptr)
    , m_refCount(Releaser<P>(m_ptr))
{

}

template<class P>
SharedPtr<P>::SharedPtr(const SharedPtr& a_other)
    : m_ptr(a_other.m_ptr)
    , m_refCount(a_other.m_refCount)
{

}

template<class P>
SharedPtr<P>& SharedPtr<P>::operator=(const SharedPtr& a_other) {
    m_ptr = a_other.m_ptr;
    m_refCount = a_other.m_refCount;

    return *this;
}

template<class P>
template<class OTHER>
SharedPtr<P>::SharedPtr(const SharedPtr<OTHER>& a_ptr)
    : m_ptr(a_ptr.m_ptr)
    , m_refCount(a_ptr.m_refCount)
{

}

template<class P>
template<class OTHER>
SharedPtr<P>& SharedPtr<P>::operator=(const SharedPtr<OTHER>& a_ptr) {     
    m_ptr = a_ptr.m_ptr; // allow conversion of pointers and base->derived
    m_refCount = a_ptr.m_refCount;

    return *this;
}


