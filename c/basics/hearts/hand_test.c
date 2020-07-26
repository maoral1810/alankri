#include <stdio.h>  /* printf     */
#include "hand.h"   /* hand API   */
#include "colors.h" /* colors     */


static void PrintResualt(char *_testName, char *_scenario , int err);
static Card BigHeart(const int *_table, Hand *_hand);

static void TestHandCreate(void);
static void TestHandDestroyNull(void);

static void TestHandAddCardValidCard(void);
static void TestHandAddCardInvalidCard(void);

static void TestHandExtractMaxCard(void);
static void TestHandExtractMaxCardHandNull(void);

static void TestHandExtrectMinCard(void);

int main(void)
{
    TestHandCreate();
    TestHandDestroyNull();

    TestHandAddCardValidCard();
    TestHandAddCardInvalidCard();

    TestHandExtractMaxCard();
    TestHandExtractMaxCardHandNull();

    TestHandExtrectMinCard();

    return 0;
}

static void TestHandCreate(void)
{
    int err = 0;
    char *testName = "TestHandCreate";
    char *scenario = "";
    
    Hand *newHand = HandCreate();

    if(newHand == NULL)
    {
        ++err;
    }

    HandDestroy(newHand);
    PrintResualt(testName, scenario, err);
}

static void TestHandDestroyNull(void)
{
    char *testName = "TestHandDestroy";
    char *scenario = "Null";

    HandDestroy(NULL);

    PrintResualt(testName, scenario, 0);
}

static void TestHandAddCardValidCard(void)
{
    int err = 0;
    char *testName = "TestHandAddCard";
    char *scenario = "ValidCard";
    Card checkCard;
    Hand *newHand = HandCreate();

    HandAddCard(newHand, GET_CARD(SPADE, TWO));

    if(GET_CARD(SPADE, TWO) != HandExtractMaxCard(newHand, SPADE))
    {
        ++err;
    }

    HandDestroy(newHand);
    
    PrintResualt(testName, scenario, err);
}

static void TestHandAddCardInvalidCard(void)
{
    int err = 0;
    char *testName = "TestHandAddCard";
    char *scenario = "InvalidCard";
    Hand *newHand = HandCreate();

    HandAddCard(newHand, GET_CARD(10, TWO));

    if(INVALID_CARD != HandExtractMaxCard(newHand, SPADE))
    {
        ++err;
    }

    HandDestroy(newHand);
    
    PrintResualt(testName, scenario, err);
}

static void TestHandExtractMaxCard(void)
{
    int err = 0;
    char *testName = "HandExtractMaxCard";
    char *scenario = "";
    Hand *newHand = HandCreate();

    HandAddCard(newHand, GET_CARD(CLUB, TWO));
    HandAddCard(newHand, GET_CARD(CLUB, QUEEN));
    HandAddCard(newHand, GET_CARD(CLUB, EIGHT));
    HandAddCard(newHand, GET_CARD(CLUB, KING));
    HandAddCard(newHand, GET_CARD(CLUB, FOUR));

    if(GET_CARD(CLUB, KING) != HandExtractMaxCard(newHand, CLUB))
    {
        ++err;
    }

    HandPrint(newHand);
    HandDestroy(newHand);
    
    PrintResualt(testName, scenario, err);
}

static void TestHandExtractMaxCardHandNull(void)
{
    int err = 0;
    char *testName = "HandExtractMaxCard";
    char *scenario = "HandNull";

    if(INVALID_CARD != HandExtractMaxCard(NULL, CLUB))
    {
        ++err;
    }

    PrintResualt(testName, scenario, err);
}

static void TestHandExtrectMinCard(void)
{
    int err = 0;
    char *testName = "TestHandExtrectMinCard";
    char *scenario = "";
    Hand *newHand = HandCreate();

    HandAddCard(newHand, GET_CARD(CLUB, TWO));
    HandAddCard(newHand, GET_CARD(CLUB, QUEEN));
    HandAddCard(newHand, GET_CARD(CLUB, EIGHT));
    HandAddCard(newHand, GET_CARD(CLUB, KING));
    HandAddCard(newHand, GET_CARD(CLUB, FOUR));
    HandPrint(newHand);

    if(GET_CARD(CLUB, TWO) != HandExtrectMinCard(newHand, CLUB))
    {
        ++err;
    }

    HandPrint(newHand);
    HandDestroy(newHand);
    
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

static Card BigHeart(const int *_table, Hand *_hand)
{
    return (DIAMOND * QUEEN);
}


