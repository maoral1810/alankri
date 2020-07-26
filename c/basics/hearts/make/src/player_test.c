#include <stdio.h>  /* printf     */
#include "player.h" /* player API */
#include "colors.h" /* colors     */


static void PrintResualt(char *_testName, char *_scenario , int err);
static Card BigHeart(int *_table, Hand *_hand);

static void TestCreatePlayerNameAndStartegyNull(void);
static void TestCreatePlayerNameNull(void);
static void TestCreatePlayerStartegyNull(void);

int main(void)
{
    TestCreatePlayerNameAndStartegyNull();
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
    int table[] = {4,20,34,51};
    Hand *hand = HandCreate();

    Player *newPlayer = PlayerCreate(NULL, BigHeart(table, hand));

    if(newPlayer != NULL)
    {
        ++err;
    }

    PrintResualt(testName, scenario, err);
}

static void TestCreatePlayerStartegyNull(void)
{
    int err = 0;
    char *testName = "TestCreatePlayer";
    char *scenario = "StartegyNull";
    int table[] = {4,20,34,51};
    Hand *hand = HandCreate();

    Player *newPlayer = PlayerCreate(NULL, BigHeart(table, hand));

    if(newPlayer != NULL)
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

static Card BigHeart(int *_table, Hand *_hand)
{
    return (DIAMOND * QUEEN);
}


