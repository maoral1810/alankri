#ifndef PARCER_HPP
#define PARCER_HPP

#include <string>

#include "common_utils.hpp"

namespace smart_home
{
class Parcer
{
public:
    // Parcer() = default;
    // ~Parcer() = default;

    void Parse(const std::string& a_str, const std::string a_delimiter, Tokens& a_tokens);
};

} // namespace smart_home

#endif //PARCER_HPP
