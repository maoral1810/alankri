#include <iostream>
#include <unistd.h>
#include "thread_pool.hpp"
#include "shared_ptr.hpp"
#include "runnable.hpp"

using experis::ThreadPool;
using experis::SharedPtr;
using experis::Runnable;

int g_arr[] = {10, 11, 12, 13, 14, 15};

class NumPrinter : public Runnable {
public:
    NumPrinter (int a_num) throw()
        : m_printerID(++s_printerID)
        , m_num(a_num)
    { }

    void Run() throw() {
        for(size_t i = 0; i < 100; ++i) {
            std::cout << "Printer ID: " << m_printerID << ", ";
            std::cout << "Num: " << m_num << "." << std::endl;
        }
    }

private:
    static int s_printerID;
    int m_printerID;
    int m_num;
};

int NumPrinter::s_printerID = 0;

int main () {
    SharedPtr<ThreadPool> tp(new ThreadPool(3, 50));

    SharedPtr<Runnable> prt1(new NumPrinter(g_arr[0]));
    SharedPtr<Runnable> prt2(new NumPrinter(g_arr[1]));
    SharedPtr<Runnable> prt3(new NumPrinter(g_arr[2]));
    SharedPtr<Runnable> prt4(new NumPrinter(g_arr[3]));
    SharedPtr<Runnable> prt5(new NumPrinter(g_arr[4]));
    SharedPtr<Runnable> prt6(new NumPrinter(g_arr[5]));
    tp->AddThread();
    tp->AddThread();
    tp->AddThread();
    for(size_t i = 0; i < 50; ++i) {
        tp->AddTask(prt1);
        tp->AddTask(prt2);
        tp->AddTask(prt3);
        tp->AddTask(prt4);
        tp->AddTask(prt5);
        tp->AddTask(prt6);
    }

    return 0;
}