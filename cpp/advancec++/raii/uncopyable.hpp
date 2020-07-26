#ifndef UNCOPYABLE_HPP_
#define UNCOPYABLE_HPP_
namespace experis{

class Uncopyable {
public:
    Uncopyable(){}
    //~Uncopyable = default
private:
    Uncopyable(const Uncopyable& a_other);
    Uncopyable& operator=(const Uncopyable& a_other);
};

}//experis

#endif //UNCOPYABLE_HPP_