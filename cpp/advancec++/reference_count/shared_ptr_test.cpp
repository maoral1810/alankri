#include <iostream> // cout
#include <memory> // static_pointer_cast , static_pointer_cast
#include "shared_ptr.hpp"
#include "reference_count.hpp"

static void ReferanceCountTest();
static void myTest();

class X {
    void Foo();
};

class DX : public X {
    void Koko();
};


int main(void) {
    //myTest();
    ReferanceCountTest();
    return 0;
}

static void ReferanceCountTest() {
    experis::SharedPtr<int> p1(new int(20)), p2, p4(new int(10));
    experis::SharedPtr<int> p3(p1);
    std::cout << *p3 << std::endl;
    p1 = p4;
    std::cout << *p1 << std::endl;
    p1 = p2;
    p1 = p3;
    bool i = p1 == p2;
    std::cout << i << std::endl;
    i = p1 == p3;
    std::cout << "equel test i = " << i << std::endl;
    i = p1 != p3;
    std::cout << "not equal i = " << i << std::endl;
    if (p2) {
        std::cout << "fail!!" << std::endl;
    }
    if (p1) {
        std::cout << "pass if test " << std::endl;
    }

    experis::SharedPtr<X> base(new DX());
    experis::SharedPtr<DX> derived(new DX());
    experis::SharedPtr<X> base2(derived);
    base = derived;
    derived = base;

    // part 2
   
/*     experis::SharedPtr<DX> dp1(new DX);
    experis::SharedPtr<const X> p5(dp1);
    p1 = dp1;
    static_pointer_cast<DX> (p1)->Koko();
    p5 = p2;
    p3 = const_pointer_cast<X> (p5); */

}


static void myTest() {
    experis::SharedPtr<int> p1;
    experis::SharedPtr<int> p2(new int (12));
    p1 = p2;
    experis::SharedPtr<int> p3(p1);

}