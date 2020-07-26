#include "logger.hpp"

#include <stdio.h> 
#include "time_stamp.hpp"

#include <iostream>
#include <fstream>

const char* fileName = "./logger.txt";

namespace smart_home
{

void Logger::Log(std::string type, const std::string a_msg, const std::string a_func)
{
    LogWrite(type, a_msg, __LINE__, __FILE__, a_func);
}

void Logger::LogWrite(std::string& a_type, const std::string a_msg, const int a_line, 
                      const std::string a_file, const std::string a_func)
{
    TimeStamp time;
    std::string stime = time.GetTimeAsString();
    std::string dataToFile = "Time[" + stime + "] ";
    dataToFile += "Type[" + a_type + "] ";
    IntToAssci(a_line);
    dataToFile += " in line[" + IntToAssci(a_line) + "]";
    dataToFile += " in File[" + a_file + "]";
    dataToFile += " in Func[" + a_func + "]: ";
    dataToFile += a_msg;

    std::ofstream file; 
    file.open(fileName,  std::ofstream::out | std::ofstream::app);
    file << dataToFile << "\n";
    file.close();
} 

} // namespace smart_home
