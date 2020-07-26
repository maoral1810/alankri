#include <stdio.h> /* printf */
#include "bitwise.h"

#define NUM_OF_BITS (sizeof(char) * 8)
#define ARR_LEN(x)(sizeof(x) / sizeof(x[0]))

static void TestCountSetBits(void);
static void TestInvertBits(void);
static void TestRotateRight(void);
static void TestSetBits(void);
static void TestMult(void);
static void TestSetBitsIToJ(void);
static void TestPackingString(void);

static void PrintBinary(unsigned char _num);
static void PrintPackString(const char *_str);
static void PrintResualt(char *_testName, char *_scenario , int err);


int main(int argc, char *argv[])
{
    TestCountSetBits();
    TestInvertBits();
    TestRotateRight();
    TestSetBits();
    TestMult();
    TestSetBitsIToJ();
    TestPackingString();

    return 0;
}

static void TestCountSetBits(void)
{
    char *testName = "TestCountSetBits";
    char *scenario = "";
    unsigned char num []= {0,1,2,3,4,5,6,7,8,9};
    unsigned char expRes []= {0,1,1,2,1,2,2,3,1,2};
    int err = 0;
    size_t i = 0;
    size_t arrSize = ARR_LEN(num);

    for( ; i < arrSize; ++i)
    {
        if(expRes[i] != CountSetBits(num[i]))
        {
            ++err;
        }
    }

    for(i = 0 ; i < arrSize; ++i)
    {
        if(expRes[i] != OptimalCountSetBits(num[i]))
        {
            ++err;
        }
    }

    PrintResualt(testName, scenario, err);
}

static void TestInvertBits(void)
{
    char *testName = "TestInvertBits";
    char *scenario = "";
    unsigned char num []= {0,1,2,3,4,5,6,7,8,9};
    unsigned char expRes []= {255,254,253,252,251,250,249,248,247,246};
    int err = 0;
    size_t i = 0;
    size_t arrSize = ARR_LEN(num);

    for( ; i < arrSize; ++i)
    {
        if(expRes[i] != InvertBits(num[i]))
        {
            ++err;
        }
    }

    PrintResualt(testName, scenario, err);
}


static void TestRotateRight(void)
{
    char *testName = "TestInvertBits";
    char *scenario = "";
    unsigned char num []= {16,8,6,4};
    unsigned char numOfRotasions []= {10,2,1,1};
    unsigned char expRes []= {4,2,3,2};
    int err = 0;
    size_t i = 0;
    size_t arrSize = ARR_LEN(num);

    for( ; i < arrSize; ++i)
    {
        if(expRes[i] != RotateRight(num[i], numOfRotasions[i]))
        {
            ++err;
        }
    }

    PrintResualt(testName, scenario, err);
}

static void TestSetBits(void)
{
    char *testName = "TestSetBits";
    char *scenario = "";
    unsigned char x []= {128,15,0,255};
    unsigned char y []= {15,15,255,0};
    unsigned char numOfbits []= {4,4,8,8};
    unsigned char position []= {6,8,8,8};
    unsigned char expRes []= {188,255,255,0};

    int err = 0;
    size_t i = 0;
    size_t arrSize = ARR_LEN(x);

    for( ; i < arrSize; ++i)
    {
        if(expRes[i] != SetBits(x[i], y[i],position[i], numOfbits[i]))
        {
            ++err;
        }
    }

    if(x[i] != SetBits(x[i], y[i],position[i], 10))
    {
        ++err;
    }

    PrintResualt(testName, scenario, err);
}           

static void TestMult(void)
{
    char *testName = "TestMult";
    char *scenario = "";
    unsigned short int x []= {5,128,0,255,20};
    unsigned short int y []= {5,2,255,0,25};
    unsigned int expRes []= {25,256,0,0,500};

    int err = 0;
    size_t i = 0;
    size_t arrSize = ARR_LEN(x);

    for( ; i < arrSize; ++i)
    {
        if(expRes[i] != Mult(x[i], y[i]))
        {
            ++err;
        }
    }

    PrintResualt(testName, scenario, err);
}

static void TestSetBitsIToJ(void)                         
{
    char *testName = "TestSetBitsIToJ";
    char *scenario = "";
    unsigned int num []= {128,255,256,4};
    unsigned char i []= {0,0,2,3};
    unsigned char j []= {7,8,4,4};
    unsigned char value[] = {1,0,0,1};
    unsigned int expRes []= {255,0,256,28};

    int err = 0;
    size_t index = 0;
    size_t arrSize = ARR_LEN(num);

    for( ; index < arrSize; ++index)
    {
        if(expRes[index] != SetBitsIToJ(num[index], i[index], j[index], value[index]))
        {
            ++err;
        }
    }

    PrintResualt(testName, scenario, err);
}

static void TestPackingString(void)                         
{
    char *testName = "TestPackingString";
    char *scenario = "";
    char str1[] = {"a"};

    int err = 0;
    size_t i = 0;

    PackingString(str1);
    PrintPackString(str1);

    PrintResualt(testName, scenario, err);
}

/* ------------------------- static functions ---------------------- */
static void PrintBinary(unsigned char _num)
{
    int i;
    
    for(i = NUM_OF_BITS - 1; i >= 0; --i)
    {
        if(_num & (1 << i))
        {
            printf("1");
        }
        else
        {
            printf("0");
        }
    }

    putchar('\n');
}

static void PrintPackString(const char *_str)
{
    while (*_str != '\0')
    {
        PrintBinary(*_str);
        ++_str;
    }
}

static void PrintResualt(char *_testName, char *_scenario , int err)
{
    if(err)
    {
        printf(BOLDCYAN"%s"BOLDYELLOW":%s: "BOLDRED"FAIL!\n"RESET,
        _testName, _scenario); 
    }
    else
    {
        printf(BOLDCYAN"%s"BOLDYELLOW":%s: "BOLDGREEN"SUCSSES \n"RESET,_testName, _scenario);
    }
}