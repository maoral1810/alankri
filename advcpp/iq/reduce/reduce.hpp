#ifndef REDUCE_HPP
#define REDUCE_HPP

#include <exception>
#include <algorithm> // for_each
#include <cstdlib>   // srand, rand 
#include <ctime>    // time

namespace advcpp {

template<class ForwaredIter, class BiFunc>
typename ForwaredIter::value_type
Reduce(ForwaredIter a_first, ForwaredIter a_last, BiFunc a_binaryFunc) 
{
    typedef typename ForwaredIter::value_type T;
    if(a_first == a_last) 
    {
        return T(); 
    }

    T result = *a_first;
    ++a_first;

    while(a_first != a_last ) 
    {
        result = a_binaryFunc(result, *a_first);
        ++a_first;
    }

    return result;
}

template <class CONT, class BINARY_FUNCTOR>
typename CONT::value_type LReduce(const CONT& a_container, BINARY_FUNCTOR a_binFunctor) 
{
    return Reduce(a_container.begin(), a_container.end(), a_binFunctor);
}

template <class CONT, class BINARY_FUNCTOR>
typename CONT::value_type RReduce(const CONT& a_container, BINARY_FUNCTOR a_binFunctor) 
{
    return Reduce(a_container.rbegin(), a_container.rend(), a_binFunctor);
}

// TODO shuffle_by_iterators

template <class CONT>
void Shuffle(CONT& a_contianer) 
{
    typedef typename CONT::value_type T;
    size_t contSize = a_contianer.size();
    size_t i = 0;
    
    srand(time(NULL));
    while(i < contSize) 
    {
        size_t randIndex = ( rand() + 51) % contSize;
        
        // swap function
        std::swap( a_contianer[i] , a_contianer[randIndex]);
        T saveData = a_contianer[i];
        a_contianer[i] = a_contianer[randIndex];
        a_contianer[randIndex] = saveData;
        
        ++i;
    }
}


template<class T>
class ReduceFunctor 
{
public:
    T operator() (const T& a_first, const T& a_second) { return a_first + a_second; }
};

} // advcpp

#endif //REDUCE_HPP__
