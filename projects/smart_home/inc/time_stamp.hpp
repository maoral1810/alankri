#ifndef TIME_STAMP_HPP
#define TIME_STAMP_HPP

#include <ctime> // struct tm

#include "common_utils.hpp"

namespace smart_home {

class TimeStamp {
public:
    TimeStamp();
    //~TimeStamp()= default;
    //TimeStamp(const TimeStamp& a_other)= default;
    //TimeStamp& operator=(const TimeStamp& a_other)= default;

    int GetSeconds() const NOEXCEPTIONS;
    int GetMinutes() const NOEXCEPTIONS;
    int GetHours() const NOEXCEPTIONS;
    std::string GetTimeAsString() const NOEXCEPTIONS;
    
    bool operator==(const TimeStamp& a_other) const NOEXCEPTIONS;
private:
    void InitilizeCurrentTime();

private:
    struct tm m_timeInfo;
};

}
#endif // TIME_STAMP_HPP




typedef struct tm TIME_STAMP;