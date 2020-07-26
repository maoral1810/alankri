#include <stdio.h>  /* FILE, */
#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc */
#include "files.h"
#include "Errors.h"
#include "colors.h"

static void TestLast(void);
static void TestOcurrenceInFile(void);
static void TestPrintDiffrence(void);
static void TestWritePersonsToFileAndRead(void);
static void TestSkipSpaces(void);
static void TestCountLettersInFile(void);
static void TestWordFrequency(void);


static void PrintResualt(char *_testName, char *_scenario , int err);

int main(void)
{
/*     TestLast();
    TestOcurrenceInFile();
    TestPrintDiffrence();
    TestWritePersonsToFileAndRead();
    TestSkipSpaces();
    TestCountLettersInFile(); */
    TestWordFrequency();

    return 0;

}

static void TestLast(void)
{
    Err status = ERR_OK;
    char *testName = "TestLast";
    char *scenario = "";
    int err = 0;

    status = Last("maor", 9);
    if (status != ERR_OK)
    {
       ++err;
    }

    status = Last("maor", 1);
    if (status != ERR_OK)
    {
       ++err;
    }
    
    status = Last("maor", 2);
    if (status != ERR_OK)
    {
       ++err;
    }

    PrintResualt(testName, scenario, err);
}

static void TestOcurrenceInFile(void)
{
    Err status = ERR_OK;
    size_t ocurrance = 0;
    char *testName = "TestOcurrenceInFile";
    char *scenario = "";
    int err = 0;

    status = OcurrenceInFile("SOMEFILE", &ocurrance);

    if(ocurrance != 3)
    {
        ++err;
    }

    ocurrance = 0;
    status = OcurrenceInFile("SOMEFILE2", &ocurrance);

    if(ocurrance != 0)
    {
        ++err;
    }

    PrintResualt(testName, scenario, err);
}

static void TestPrintDiffrence(void)
{
    Err status = ERR_OK;
    char *testName = "TestPrintDiffrence";
    char *scenario = "";
    int err = 0;

    status = PrintDiffrence("maor", "maor2");

    if(status!= ERR_OK)
    {
        ++err;
    }

    PrintResualt(testName, scenario, err);
}

static void TestWritePersonsToFileAndRead(void)
{
    Err status = ERR_OK;
    char *testName = "TestWritePersonsToFileAndRead";
    char *scenario = "";
    int err = 0;

    status = WritePersonsToFileAndRead("binaryfile");

    if(status != ERR_OK)
    {
        ++err;
    }

    PrintResualt(testName, scenario, err);
}

static void TestSkipSpaces(void)
{
    Err status = ERR_OK;
    char *testName = "TestSkipSpaces";
    char *scenario = "";
    int err = 0;

    status = SkipSpaces("maor");

    if(status != ERR_OK)
    {
        ++err;
    }

    PrintResualt(testName, scenario, err); 
}

static void TestCountLettersInFile(void)
{
    Err status = ERR_OK;
    char *testName = "TestCountLettersInFile";
    char *scenario = "";
    int err = 0;

    CountLettersInFile("maor");

    if(status != ERR_OK)
    {
        ++err;
    }

    PrintResualt(testName, scenario, err); 
}

static void TestWordFrequency(void)
{
    Err status = ERR_OK;
    char *testName = "TestWordFrequency";
    char *scenario = "";
    int err = 0;
    
    status = WordFrequency("maor");

    if(status != ERR_OK)
    {
        ++err;
    }

    PrintResualt(testName, scenario, err); 
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