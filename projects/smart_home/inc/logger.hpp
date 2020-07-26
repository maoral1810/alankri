#ifndef LOGGGER_HPP
#define LOGGGER_HPP

//#define LOG(_type,_str) LogWrtie(_type, _str, __LINE__, __FILE__, __func__)

#include <string>

namespace smart_home
{
class Logger
{
public:

public:
    // Logger() = default;
    // ~Logger() = default;

    void Log(std::string a_type, const std::string a_msg, const std::string a_func);
private:
    void LogWrite(std::string& a_type, const std::string a_msg, const int a_line, 
                          const std::string a_file, const std::string a_func);
};

} // namespace smart_home
#endif //LOGGGER_HPP