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

//------------------------smartHome-------------------------------------
#include <tr1/memory>
#include <tr1/unordered_map>
#include <vector>
#include <sys/sysinfo.h> // get_nprocs_conf
#include <exception>
#include <string>
#include <algorithm>
#include <iostream> //TODO cout
#include <dlfcn.h> // RTLD_NOW

#define Shared_Ptr std::tr1::shared_ptr
#define UNUSED(a)(void(a))

namespace smart_home
{
const size_t NUM_OF_CHANNELS = get_nprocs_conf();

class DistributionInfo;
class IHandleEvent;
class Event;
class EventChannel;
class IEventAddressPusher;
class Runnable;

typedef std::vector<DistributionInfo>::iterator SubscribersListItr;
typedef std::pair<Shared_Ptr<Event>, Shared_Ptr<IHandleEvent> > EventAddress;
typedef std::vector<Shared_Ptr<EventChannel> > ChannelsQueues;
typedef std::vector<Shared_Ptr<EventChannel> > ChannelPushers;
typedef std::vector<Shared_Ptr<Runnable> > ThreadGroupTasks;
typedef std::vector<std::string> Tokens;

const std::string Info_Delimiter = ":";
const std::string Topic_Delimiter = "~";
const std::string Event_Type_Delimiter = "^";

const size_t POSSIBLE_KEYS = 8;
const std::string ANY = "*";
//const char* SOLiabry = "./libAgent.so";


// ----------------- Shutdown Exception ------------------
class ShutdownExp : public std::exception
{
    virtual const char* what() const throw()
    {
        return ("System is shuting down");
    }
};

class EventChannelShutdownExp : public std::exception
{
    virtual const char* what() const throw()
    {
        return ("Event Channel is shuting down");
    }
};

class EventBusShutdownExp : public std::exception
{
    virtual const char* what() const throw()
    {
        return ("Event Bus is shuting down");
    }
};

// ----------------- Int To Assci ------------------

inline std::string IntToAssci(int a_val)
{
    std::string res;
    bool negtive = (a_val < 0);
    if(negtive)
    {
        a_val *= -1;
    }

    else if(a_val == 0)
    {
        res += "0";
    }

    while(a_val > 0)
    {
        char num = (a_val % 10) + '0';
        res += num;
        a_val /= 10;
    }

    if(negtive)
    {
        res += "-";
    }

    std::reverse(res.begin(),res.end());
    
    return res;
}
//----------------------- SoLibHandler -------------------------
class SoLibHandler 
{
public:
    SoLibHandler(const char* filename, int flags = RTLD_NOW) {
        m_handle = dlopen(filename, flags);
        if(m_handle == 0) {
            throw dlerror();
        }
    }
    ~SoLibHandler() {
        dlclose(m_handle);
    }
    template <typename PF>
    PF getFunction(const char* name)
    {
        void* ps = dlsym(m_handle, name);
        if(ps == 0)
        {
            throw dlerror();
        }
        
        return reinterpret_cast<PF>(ps);
    }
private:
    void* m_handle;
};


} // namespace smart_home


#endif //COMMON_UTILS_HPP