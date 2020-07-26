template<class FUNCTOR>
RefCount<FUNCTOR>::RefCount(FUNCTOR a_deleteFunc)
    : m_counter(new COUNTER_TYPE(1))
    , m_deleteFunc(a_deleteFunc)
{
    
}

template<class FUNCTOR>
RefCount<FUNCTOR>::RefCount(const RefCount& a_other)
   : m_counter(increaceRefCount(a_other.m_counter))
   , m_deleteFunc(a_other.m_deleteFunc)
{

}

template<class FUNCTOR>
RefCount<FUNCTOR>& RefCount<FUNCTOR>::operator=(const RefCount& a_other) {
    COUNTER_TYPE* otherCounter = increaceRefCount(a_other.m_counter); // to avoid self assigment
    decreaseAndTerminate();
    m_deleteFunc = a_other.m_deleteFunc;
    m_counter = otherCounter;
    return *this;
}

template<class FUNCTOR>
RefCount<FUNCTOR>::~RefCount() {
    decreaseAndTerminate();
}


/* template<class FUNCTOR>
RefCount<FUNCTOR>& RefCount<FUNCTOR>::operator--() {
    --(*m_counter);
    checkAndTerminate();
    return *this;
} */

template<class FUNCTOR>
RefCount<FUNCTOR>& RefCount<FUNCTOR>::operator++() {
    __sync_add_and_fetch(m_counter, 1);
    return *this;
}

template<class FUNCTOR>
typename RefCount<FUNCTOR>::COUNTER_TYPE* RefCount<FUNCTOR>::increaceRefCount(COUNTER_TYPE* a_other) {
    COUNTER_TYPE* otherCounter = a_other;
    ++(*otherCounter);
    return otherCounter;
}

template<class FUNCTOR>
void RefCount<FUNCTOR>::decreaseAndTerminate() {
    const COUNTER_TYPE counterrAfterDecrement = __sync_sub_and_fetch(m_counter, 1);
    if(0 == counterrAfterDecrement) {
        m_deleteFunc();
        delete m_counter;
    }
}

template<class FUNCTOR>
template<class OTHER>
RefCount<FUNCTOR>::RefCount(const RefCount<OTHER>& a_other) 
   : m_counter(increaceRefCount((a_other.m_counter)))
   , m_deleteFunc(a_other.m_deleteFunc)
{

}
