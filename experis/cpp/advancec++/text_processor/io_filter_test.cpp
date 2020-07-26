#include <iostream>
#include <string>
#include <iostream> // cout
#include <cstring>
#include "MUTest.h"
#include "string_input.hpp"
#include "string_output.hpp"
#include "to_upper.hpp"

// ---------------------- static functions --------------------

UNIT (inputString)
    char buffer[50];
    std::string* str = new std::string("blabla");
    experis::StringInput input(str);
    
    size_t readResult = input.Read(buffer, sizeof(buffer));
    
    ASSERT_THAT(readResult == str->size());
    ASSERT_THAT(!str->compare(buffer));

    delete str;

END_UNIT

UNIT (OutputString)
    char buffer[50];
    std::string* str = new std::string("kiskos");
    experis::StringInput input(str);
    
    size_t readResualt =  input.Read(buffer, sizeof(buffer));

    std::string* str2 = new std::string("777");
    experis::StringOutput output(str2);

    size_t writeResualt = output.Write(buffer, readResualt);
    
    ASSERT_THAT(writeResualt == readResualt);
    ASSERT_THAT(!str2->compare(*str));

    delete str;
    delete str2;

END_UNIT

UNIT(ToUpper)
    char buffer[50];
    std::string* str = new std::string("kiskos");
    experis::StringInput input(str);
    
    size_t readResualt =  input.Read(buffer, sizeof(buffer));
    experis::ToUpper toUpFilter;
    toUpFilter.FilterStream(buffer, readResualt);

    ASSERT_THAT(!strcmp(buffer,"KISKOS"));

END_UNIT

TEST_SUITE(IoTest)

    TEST(inputString)
    TEST(OutputString)
    TEST(ToUpper)

END_SUITE



