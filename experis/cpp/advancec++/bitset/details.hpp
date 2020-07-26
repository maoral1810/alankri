#ifndef DETAILS_HPP_
#define DETAILS_HPP_

#include <cstddef> // size_t 

namespace details {
    typedef unsigned long BITSET_TYPE;
    static const size_t BITS_IN_BYTE = 8;
    static const size_t NUM_OF_BITS = BITS_IN_BYTE * sizeof(BITSET_TYPE);
}// details

#endif //DETAILS_HPP_