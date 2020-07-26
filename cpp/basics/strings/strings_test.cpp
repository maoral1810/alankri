#include <iostream>     //cout
#include <string.h>     //strlen
#include <stdio.h>      //printf
#include "colors.h"
#include "strings.h"

using std::cout;
using std::endl;

static void PrintResualt(const char *_testName, const char *_scenario, int err);

static void TestDefaultCtor(void);
static void TestCtor(void);
static void TestCCtor(void);
static void TestLength(void);
static void TestToUpper(void);
static void TestToLower(void);
static void TestPrepend(void);
static void TestOperators(void);
static void TestContains(void);
static void TestNumOfObj(void);
static void TestFirstOccurence(void);
static void TestLastOccurence(void);
static void TestGetCapcity(void);
static void TestCaseSensitiveState(void);

int main()
{
    TestDefaultCtor();
    TestCtor();
    TestCCtor();
    TestLength();
    TestToUpper();
    TestToLower();
    TestPrepend();
    TestOperators();
    TestContains();
    TestNumOfObj();
    TestFirstOccurence();
    TestLastOccurence();
    TestGetCapcity();
    TestCaseSensitiveState();

    return 0;
}

static void TestDefaultCtor(void)
{
    const char *testName = "TestDefaultCtor";
    const char *scenario = "";
    int err = 0;
    String_t testStr;
    String_t toCompere;

    testStr.SetString("maor");

    if(!testStr.Compare(toCompere))
    {
        ++err;
    } 

    PrintResualt(testName, scenario, err);
}

static void TestCtor(void)
{
    const char *testName = "TestCtor";
    const char *scenario = "";
    int err = 0;
    String_t testStr("Test");
    String_t toCompare("Test");

    if(testStr.Compare(toCompare))
    {
        ++err;
    } 

    PrintResualt(testName, scenario, err);
}

static void TestCCtor(void)
{
    const char *testName = "TestCCtor";
    const char *scenario = "";
    int err = 0;
    String_t testStr("Test");
    String_t toCopy;
    
    toCopy = testStr;

    if(testStr.Compare(toCopy))
    {
        ++err;
    } 

    PrintResualt(testName, scenario, err);
}

static void TestLength(void)
{
    const char *testName = "TestLength";
    const char *scenario = "";
    int err = 0;
    const char *str = "Test";
    String_t testStr(str);
    size_t len = strlen(str);

    if(testStr.Length() != len)
    {
        ++err;
    }
    if(testStr.Compare(testStr) != 0)
    {
        ++err;
    }

    testStr.SetString("");

    if(testStr.Length() != len)
    {
        ++err;
    }

    PrintResualt(testName, scenario, err);
}

static void TestToUpper(void)
{
    const char *testName = "TestToUpper";
    const char *scenario = "";
    int err = 0;

    String_t testStr("Test");
    String_t toCompere("TEST");

    testStr.ToUpper();

    if (testStr != toCompere)
    {
        ++err;
    }

    PrintResualt(testName, scenario, err);
}

static void TestToLower(void)
{
    const char *testName = "TestToLower";
    const char *scenario = "";
    int err = 0;
    String_t testStr("TestToLower");
    String_t toCompere("testtolower");

    testStr.ToLower();
    if (testStr != toCompere)
    {
        ++err;
    }

    PrintResualt(testName, scenario, err);
}

static void TestPrepend(void)
{
    const char *testName = "TestPrepend";
    const char *scenario = "";
    int err = 0;
    String_t testStr("Start");
    String_t toAdd("End");
    String_t excREs("EndStart");

    testStr.Prepend(toAdd);

    if(testStr != excREs)
    {
        ++err;
    }

    testStr.SetString("Start");
    testStr.Prepend("End");

    if(testStr != excREs)
    {
        ++err;
    }

    testStr.SetString("Start");
    testStr.Prepend("");
    excREs.SetString("Start");

    if(testStr != excREs)
    {
        ++err;
    }   

    PrintResualt(testName, scenario, err);
}

static void TestOperators(void)
{
    const char *testName = "TestOperators";
    const char *scenario = "";
    int err = 0;
    String_t testStr("Start");
    String_t toAdd("End");
    String_t SameStr("Start");
    
    if(toAdd > testStr)
    {
        ++err;
    }

    if(testStr < toAdd)
    {
        ++err;
    }

    if(toAdd == testStr)
    {
        ++err;
    }

    if(testStr != SameStr)
    {
        ++err;
    }

    if(testStr[1] != 't')
    {
        ++err;
    }

    SameStr = testStr(2,3);

    if(SameStr != "art")
    {
        ++err;
    }
    
    testStr[2] = 'p';

    SameStr.SetString("stprt");

    if(SameStr != testStr)
    {
        ++err;
    }

    PrintResualt(testName, scenario, err);
}

static void TestContains(void)
{
    const char *testName = "TestContains";
    const char *scenario = "";
    int err = 0;
    String_t testStr("banana");
    String_t toSerch("na");

    if(!testStr.Contains(toSerch))
    {
        ++err;
    }

    PrintResualt(testName, scenario, err);
}

static void TestNumOfObj(void)
{
    const char *testName = "TestNumOfObj";
    const char *scenario = "";
    int err = 0;
    
    String_t testStr("banana");

    if(testStr.NumOfObj()!= 1)
    {
        ++err;
    }

    String_t toSerch("na");

    if(testStr.NumOfObj()!= 2)
    {
        ++err;
    }

    PrintResualt(testName, scenario, err);
}

static void TestFirstOccurence(void)
{
    const char *testName = "TestFirstOccurence";
    const char *scenario = "";
    int err = 0;
    
    String_t testStr("banana");

    if(testStr.FirstOccurence('n') != 2)
    {
        ++err;
    }

    if(testStr.FirstOccurence('b') != 0)
    {
        ++err;
    }

    if(testStr.FirstOccurence('a') != 1)
    {
        ++err;
    }

    PrintResualt(testName, scenario, err);
}

static void TestLastOccurence(void)
{
    const char *testName = "TestLastOccurence";
    const char *scenario = "";
    int err = 0;
    
    String_t testStr("banana");

    if(testStr.LastOccurence('n') != 4)
    {
        ++err;
    }

    if(testStr.LastOccurence('b') != 0)
    {
        ++err;
    }

    if(testStr.LastOccurence('a') != 5)
    {
        ++err;
    }

    PrintResualt(testName, scenario, err);
}

static void TestGetCapcity(void)
{
    const char *testName = "TestGetCapcity";
    const char *scenario = "";
    int err = 0;
    
    String_t testStr("bananananana");

    if(testStr.GetCapcity() != 16)
    {
        ++err;
    }

    testStr.SetString("i need to increase my capcity twice :) hhhhhhhhh");

    if(testStr.GetCapcity() != 16 * 4)
    {
        ++err;
    }

    PrintResualt(testName, scenario, err);
}

static void TestCaseSensitiveState(void)
{
    const char *testName = "TestCaseSensitiveState";
    const char *scenario = "";
    int err = 0;
    
    String_t testStr("banana");
    String_t toCompere("BaNaNa");
    String_t toFind("An");

    if(testStr.Compare(toCompere))
    {
        ++err;
    }

    if(toCompere.FirstOccurence('N') != 2 && toCompere.FirstOccurence('n') != 2)
    {
        ++err;
    }

    if(toCompere.LastOccurence('N') != 4 && toCompere.LastOccurence('n') != 4)
    {
        ++err;
    }


    if(testStr > toCompere || testStr < toCompere || testStr != toCompere 
       ||  !(testStr >= toCompere) || !(testStr <= toCompere))
    {
        ++err;
    }

    if(!testStr.Contains(toFind))
    {
        ++err;
    }

    String_t::CaseSensitiveState(1);
    
    if(!testStr.Compare(toCompere))
    {
        ++err;
    }

    if(toCompere.FirstOccurence('N') != 2)
    {
        ++err;
    }

    if(testStr.Contains(toFind))
    {
        ++err;
    }

    PrintResualt(testName, scenario, err);
}

/* --------------------- static functions ------------------------------------*/
static void PrintResualt(const char *_testName, const char *_scenario, int err)
{
    if (err)
    {
        printf(BOLDCYAN "%s" BOLDYELLOW ":%s: " BOLDRED "FAIL!\n" RESET,
               _testName, _scenario);
    }
    else
    {
        printf(BOLDCYAN "%s" BOLDYELLOW ":%s: " BOLDGREEN "SUCSSES \n" RESET, _testName, _scenario);
    }
}

