#include <stdio.h>  /* printf    */
#include "table.h"  /* table API */
#include "colors.h" /* colors    */


static void PrintResualt(char *_testName, char *_scenario , int err);

static void TestTableAddCard(void);

int main(void)
{
    TestTableAddCard();
    
    return 0;
}

static void TestTableAddCard(void)
{
    int err = 0;
    char *testName = "TestTableAddCard";
    char *scenario = "add + calc";
    Table table[4] = {0};
    size_t i = 0;
    size_t losserIndex;

    Card cardArr[] = {GET_CARD(HEART, FOUR), GET_CARD(HEART, TWO), 
                      GET_CARD(SPADE, QUEEN), GET_CARD(CLUB, KING)};
    size_t expResualt = 15;

    for( i = 0; i < 4; ++i)
    {
        TableAddCard(table, i, cardArr[i]);    
    }

    TablePrint(table, 4);


    if (expResualt != TableCalcLoser (table, 4, 0, &losserIndex) &&
        losserIndex != 0)
    {
        ++err;
    }  
			
    PrintResualt(testName, scenario, err);
}

/*------------- helpful functions -------------------------*/
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

