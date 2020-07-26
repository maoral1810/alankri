#ifndef COMMON_UTILS_HPP
#define COMMON_UTILS_HPP

//--------------------- MACROS And Constants ------------------
#define NOEXCEPTIONS throw()
inline unsigned long MicroToMili(unsigned long a_time){ return a_time / 1000;}
inline unsigned long MicroToNano(unsigned long a_time){ return a_time * 1000;}

//-------------------------- Uncopyable -----------------
class Uncopyable 
{
protected:
    Uncopyable();
    ~Uncopyable();
private:
    Uncopyable(const Uncopyable& a_other);
    Uncopyable& operator=(const Uncopyable& a_other);
};

class Unassignable 
{
protected:
    Unassignable();
    ~Unassignable();
private:
    Unassignable& operator=(const Unassignable& a_other);
};


inline Uncopyable::Uncopyable()
{}

inline Uncopyable::~Uncopyable()
{}

inline Unassignable::Unassignable()
{}

inline Unassignable::~Unassignable()
{}

//------------------------ Atomic Value & Atomic Bool -------------------------- 
template<typename T>
// require T(), T is integer type only (byte...8 bytes)
class AtomicValue {
public:
    explicit AtomicValue(const T& a_val = T())NOEXCEPTIONS;
    // ~AtomicValue() = default;
    // AtomicValue(const AtomicValue& a_other) = default;
    // AtomicValue& operator=(const AtomicValue& a_other) = default;

    T operator++()NOEXCEPTIONS;
    T operator--()NOEXCEPTIONS;
    void operator+=(T a_val) NOEXCEPTIONS;
    void operator-=(T a_val) NOEXCEPTIONS;
    //bool operator==(const AtomicValue& a_other);
    T Value() const NOEXCEPTIONS;
    void Value(T a_val) NOEXCEPTIONS;

private:    
    T m_value;
};

template<typename T>
AtomicValue<T>::AtomicValue(const T& a_val) NOEXCEPTIONS
    : m_value(a_val)
{}

template<typename T>
T AtomicValue<T>::operator++() NOEXCEPTIONS
{
    return __sync_add_and_fetch(&m_value ,1);
}

template<typename T>
T AtomicValue<T>::operator--() NOEXCEPTIONS
{
    return __sync_sub_and_fetch(&m_value ,1);
}

template<typename T>
void AtomicValue<T>::operator+=(T a_val) NOEXCEPTIONS
{
    (void)__sync_add_and_fetch(&m_value ,a_val);
}

template<typename T>
void AtomicValue<T>::operator-=(T a_val) NOEXCEPTIONS
{
    (void)__sync_add_and_fetch(&m_value , a_val);
}

template<typename T>
T AtomicValue<T>::Value() const NOEXCEPTIONS
{
   return m_value;//__sync_lock_test_and_set(&m_value, m_value); // how to to???
}

template<typename T>
void AtomicValue<T>::Value(T a_val) NOEXCEPTIONS
{
    (void)__sync_lock_test_and_set(&m_value, a_val);
}
//-------------- spcielization of Atomic Bool --------------- 
template<>
// require T(), T is integer type only (byte...8 bytes)
class AtomicValue<bool> {
public:
    explicit AtomicValue(bool a_val) NOEXCEPTIONS;
    // ~AtomicValue() = default;
    // AtomicValue(const AtomicValue& a_other) = default;
    // AtomicValue& operator=(const AtomicValue& a_other) = default;

    bool Aquire() NOEXCEPTIONS;
    bool Release() NOEXCEPTIONS;
    bool Get() const NOEXCEPTIONS;

private:
    bool m_value;
};

inline AtomicValue<bool>::AtomicValue(bool a_val) NOEXCEPTIONS
    : m_value(a_val)
{}

inline bool AtomicValue<bool>::Aquire() NOEXCEPTIONS
{
    return __sync_lock_test_and_set(&m_value, true);
}

inline bool AtomicValue<bool>::Release() NOEXCEPTIONS
{
    return __sync_lock_test_and_set(&m_value, false);
}

inline bool AtomicValue<bool>::Get() const NOEXCEPTIONS
{
    return m_value; //__sync_lock_test_and_set(&m_value, m_value); // by atomic operation! which?
}

//------------------------------------------------------------------

#endif //COMMON_UTILS_HPP