#include <stdio.h>  /* printf     */
#include "player.h" /* player API */
#include "colors.h" /* colors     */


static void PrintResualt(char *_testName, char *_scenario , int err);
static Card BigHeart(const int *_table, Hand *_hand);

static void TestCreatePlayerNameAndStartegyNull(void);
static void TestCreatePlayerNameNull(void);
static void TestCreatePlayerStartegyNull(void);

static void TestPlayerDestroyNULL(void);

static void TestPlayerAddCardValidCard(void);
static void TestPlayerAddCardInvalidCard(void);
static void TestPlayerAddCardPlayerNull(void);

static void TestPlayerAddScore50Points(void);
static void TestPlayerAddScorePlayerNull(void);

int main(void)
{
    TestCreatePlayerNameAndStartegyNull();
    TestCreatePlayerNameNull();
    TestCreatePlayerStartegyNull();

    TestPlayerDestroyNULL();

    TestPlayerAddCardValidCard();
    TestPlayerAddCardInvalidCard();
    TestPlayerAddCardPlayerNull();

    TestPlayerAddScore50Points();
    TestPlayerAddScorePlayerNull();
    
    return 0;
}

static void TestCreatePlayerNameAndStartegyNull(void)
{
    int err = 0;
    char *testName = "TestCreatePlayer";
    char *scenario = "NameAndStartegyNull";
    
    Player *newPlayer = PlayerCreate(NULL, NULL);

    if(newPlayer != NULL)
    {
        ++err;
    }

    PrintResualt(testName, scenario, err);
}

static void TestCreatePlayerNameNull(void)
{
    int err = 0;
    char *testName = "TestCreatePlayer";
    char *scenario = "NameNull";

    Player *newPlayer = PlayerCreate(NULL, BigHeart);

    if(newPlayer == NULL)
    {
        ++err;
    }

    PlayerDestroy(newPlayer);

    PrintResualt(testName, scenario, err);
}

static void TestCreatePlayerStartegyNull(void)
{
    int err = 0;
    char *testName = "TestCreatePlayer";
    char *scenario = "StartegyNull";

    Player *newPlayer = PlayerCreate("MAOR", NULL);

    if(newPlayer != NULL)
    {
        ++err;
    }

    PrintResualt(testName, scenario, err); 
}

static void TestPlayerDestroyNULL(void)
{
    char *testName = "TestPlayerDestroy";
    char *scenario = "NULL";

    PlayerDestroy(NULL);

    PrintResualt(testName, scenario, 0); 
}

static void TestPlayerAddCardValidCard(void)
{
    int err = 0;
    char *testName = "TestPlayerAddCard";
    char *scenario = "ValidCard";


    Player *newPlayer = PlayerCreate("MAOR", BigHeart);

    if(HEARTS_OK != PlayerAddCard(newPlayer, DIAMOND * ACE))
    {
        ++err;
    }
    
    PlayerDestroy(newPlayer);

    PrintResualt(testName, scenario, err); 
}

static void TestPlayerAddCardInvalidCard(void)
{
    int err = 0;
    char *testName = "TestPlayerAddCard";
    char *scenario = "InvalidCard";


    Player *newPlayer = PlayerCreate("MAOR", BigHeart);

    if(HEARTS_WRONG_CARD != PlayerAddCard(newPlayer, 53))
    {
        ++err;
    }
    
    PlayerDestroy(newPlayer);

    PrintResualt(testName, scenario, err); 
}

static void TestPlayerAddCardPlayerNull(void)
{
    int err = 0;
    char *testName = "TestPlayerAddCard";
    char *scenario = "PlayerNull";


    if(HEARTS_NOT_INITIALIZED != PlayerAddCard(NULL, 53))
    {
        ++err;
    }

    PrintResualt(testName, scenario, err); 
}

static void TestPlayerAddScore50Points(void)
{
    int err = 0;
    char *testName = "TestPlayerAddCard";
    char *scenario = "50 points";
    size_t playerScore;

    Player *newPlayer = PlayerCreate("MAOR", BigHeart);

    if( HEARTS_OK != PlayerGetScore(newPlayer, &playerScore) && playerScore != 0)
    {
        ++err;
    }

    if(HEARTS_OK != PlayerAddScore(newPlayer, 50))
    {
        ++err;
    }

    if( HEARTS_OK != PlayerGetScore(newPlayer, &playerScore) && playerScore != 50)
    {
        ++err;
    }

    PlayerDestroy(newPlayer);

    PrintResualt(testName, scenario, err); 
}

static void TestPlayerAddScorePlayerNull(void)
{
    int err = 0;
    char *testName = "TestPlayerAddCard";
    char *scenario = "PlayerNull";

    if(HEARTS_NOT_INITIALIZED != PlayerAddScore(NULL, 50))
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

static Card BigHeart(const int *_table, Hand *_hand)
{
    return (DIAMOND * QUEEN);
}


