#include <iostream>
#include "template_string.hpp"


void TStringTest();
void TStringWcharTest();

int main() {
    TStringTest();
    TStringWcharTest();
    return 0;
}

void TStringTest() {
    experis::TString<char> str;
    experis::TString<char> str2("ridan");
    if (0 == str.GetStr()) {
        std::cout << "yes" << std::endl;
        std::cout << str2.GetStr() << std::endl;
    }
    experis::TString<char> strCpy(str2);
    std::cout << strCpy.GetStr() << std::endl;
    strCpy = "hello";
    std::cout << strCpy.GetStr() << std::endl;
    if (str2 == strCpy) {
        std::cout << "work" << std::endl;
    }
}

void TStringWcharTest() {
    experis::TString<wchar_t> str;
    experis::TString<wchar_t> str2(L"ridan");
    if (0 == str.GetStr()) {
        std::cout << "yes" << std::endl;
        std::cout << str2.GetStr() << std::endl;
    }
    experis::TString<wchar_t> strCpy(str2);
    std::wcout << strCpy.GetStr() << std::endl;
    strCpy = L"hello";
    std::wcout << strCpy.GetStr() << std::endl;
    if (str2 == strCpy) {
        std::cout << "work" << std::endl;
    }

}