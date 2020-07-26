#include "parcer.hpp"
#include "common_utils.hpp"

namespace smart_home
{
void Parcer::Parse(const std::string& a_str, const std::string a_delimiter, Tokens& a_tokens)
{
    size_t current, previous = 0;
    current = a_str.find_first_of(a_delimiter);
    while (current != std::string::npos) {
        a_tokens.push_back(a_str.substr(previous, current - previous));
        previous = current + 1;
        current = a_str.find_first_of(a_delimiter, previous);
    }
}

} // namespace smart_home`
