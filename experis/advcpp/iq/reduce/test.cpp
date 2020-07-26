#include <string>
#include <vector>
#include <iostream> // cout
#include <cmath>    // pow
#include "reduce.hpp"
#include "mu_test.h"

UNIT (StringLReduceTest)
    std::cout << "--------- LReduce ------------" << '\n';
    typedef std::string VAL_TYPE;
    typedef std::vector<std::string> CONTAINER_TYPE;
    CONTAINER_TYPE vec(11);

    vec.push_back("1-> ");
    vec.push_back("2-> ");
    vec.push_back("3-> ");
    vec.push_back("4-> ");
    vec.push_back("5-> ");
    vec.push_back("6-> ");
    vec.push_back("7-> ");
    vec.push_back("8-> ");
    vec.push_back("9-> ");
    vec.push_back("10-> ");
    vec.push_back("End");

    VAL_TYPE result = advcpp::LReduce(vec, advcpp::ReduceFunctor<VAL_TYPE>() );
    std::cout << result << '\n';

    ASSERT_EQUAL(result , "1-> 2-> 3-> 4-> 5-> 6-> 7-> 8-> 9-> 10-> End");
END_UNIT

UNIT (IntLReduceTest)
    typedef int VAL_TYPE;
    typedef std::vector<VAL_TYPE> CONTAINER_TYPE;
    CONTAINER_TYPE vec(7, 6);
    VAL_TYPE result = advcpp::LReduce(vec, advcpp::ReduceFunctor<VAL_TYPE>() );

    ASSERT_EQUAL(result, 42);

END_UNIT

UNIT (StringRReduceTest)
    std::cout << "--------- RReduce ------------" << '\n';
    typedef std::string VAL_TYPE;
    typedef std::vector<std::string> CONTAINER_TYPE;
    CONTAINER_TYPE vec(11);

    vec.push_back("1 ");
    vec.push_back("2-> ");
    vec.push_back("3-> ");
    vec.push_back("4-> ");
    vec.push_back("5-> ");
    vec.push_back("6-> ");
    vec.push_back("7-> ");
    vec.push_back("8-> ");
    vec.push_back("9-> ");
    vec.push_back("10-> ");
    vec.push_back("End-> ");

    VAL_TYPE backwardResult =  advcpp::RReduce(vec, advcpp::ReduceFunctor<VAL_TYPE>() );
    std::cout << backwardResult << '\n';
    
    ASSERT_EQUAL(backwardResult , "End-> 10-> 9-> 8-> 7-> 6-> 5-> 4-> 3-> 2-> 1 "); 
END_UNIT

UNIT (IntRReduceTest)
    typedef int VAL_TYPE;
    typedef std::vector<VAL_TYPE> CONTAINER_TYPE;
    CONTAINER_TYPE vec(7, 6);
    VAL_TYPE result =  advcpp::RReduce(vec, advcpp::ReduceFunctor<VAL_TYPE>() );

    ASSERT_EQUAL(result, 42);
END_UNIT

UNIT (DoubleLReduceTest)
    typedef double VAL_TYPE;
    typedef std::vector<VAL_TYPE> CONTAINER_TYPE;
    CONTAINER_TYPE vec(3, 2000000000033.15); 
    VAL_TYPE result =  advcpp::LReduce(vec, advcpp::ReduceFunctor<VAL_TYPE>() );

    ASSERT_NOT_EQUAL(result, 6000000000099.45); // double is not accurate type
END_UNIT

UNIT(LReduceEmptyContTest)
    typedef double VAL_TYPE;
    typedef std::vector<VAL_TYPE> CONTAINER_TYPE;
    CONTAINER_TYPE vec;
    VAL_TYPE result = advcpp::LReduce(vec, advcpp::ReduceFunctor<VAL_TYPE>() );

    ASSERT_EQUAL(result, 0);
END_UNIT

UNIT(RReduceEmptyContTest)
    typedef double VAL_TYPE;
    typedef std::vector<VAL_TYPE> CONTAINER_TYPE;
    CONTAINER_TYPE vec;
    VAL_TYPE result = advcpp::RReduce(vec, advcpp::ReduceFunctor<VAL_TYPE>() );

    ASSERT_EQUAL(result, 0);
END_UNIT

UNIT(Geometric_Series_down_100000_elements_Test)
    std::cout << "--------- Geometric Series ------------" << '\n';
    typedef double VAL_TYPE;
    typedef std::vector<VAL_TYPE> CONTAINER_TYPE;

    size_t vectorSize = 100000;
    CONTAINER_TYPE vec(vectorSize);
    size_t i = 0;
    double num = 1.2;
    double factor = 0.3;

    while(i < vectorSize)
    {
        vec[i] = num * pow(factor, i);
        ++i;
    }

    advcpp::Shuffle(vec);

    VAL_TYPE result = advcpp::RReduce(vec, advcpp::ReduceFunctor<VAL_TYPE>() );
    std::cout << "result = " << result << '\n';
    ASSERT_EQUAL(result, num * ( (1 - pow(factor, vectorSize)) / (1 - factor) ));

END_UNIT

UNIT(Geometric_Series_up_100000_elements_Test)
    typedef double VAL_TYPE;
    typedef std::vector<VAL_TYPE> CONTAINER_TYPE;

    size_t vectorSize = 100000;
    CONTAINER_TYPE vec(vectorSize);
    size_t i = 0;
    double num = 1.2;
    double factor = 1.8;

    while(i < vectorSize)
    {
        vec[i] = num * pow(factor, i);
        ++i;
    }

    advcpp::Shuffle(vec);

    VAL_TYPE result = advcpp::RReduce(vec, advcpp::ReduceFunctor<VAL_TYPE>() );
    std::cout << "result = " << result << '\n';
    ASSERT_EQUAL(result, num * ( (1 - pow(factor, vectorSize)) / (1 - factor) ));

END_UNIT


TEST_SUITE(Reduce_Test)
    // -------- LReduce ---------- 
    TEST(StringLReduceTest)
    TEST(IntLReduceTest)
    TEST(LReduceEmptyContTest)
    TEST(DoubleLReduceTest)
    //--------- RReduce ------------
    TEST(StringRReduceTest)
    TEST(IntRReduceTest)
    TEST(RReduceEmptyContTest)
    // -------- Geometric Series ----------
    TEST(Geometric_Series_down_100000_elements_Test)
    TEST(Geometric_Series_up_100000_elements_Test)

END_SUITE
