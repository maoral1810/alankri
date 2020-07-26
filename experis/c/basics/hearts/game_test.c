#include <stdio.h> /* printf */
#include "game.h"
#include "colors.h"

static void PrintResualt(char *_testName, char *_scenario , int err);

static void TestGameCreateAndDestroy(void);

static void TestGameDestroyGameNull(void);
static void TestGameDestroyDoubleFree(void);

static void TestGamePlayGameNULL(void);
static void TestGamePlayGame(void);


int main(void)
{
    TestGameCreateAndDestroy();

    TestGameDestroyGameNull();
    TestGameDestroyDoubleFree();

    TestGamePlayGameNULL();
    TestGamePlayGame();

    return 0;
}

static void TestGameCreate(void)
{
    int err = 0;
    char *testName = "TestGameCreate";
    char *scenario = "";

    Game *newGame = GameCreate();

    if(newGame == NULL)
    {
        ++err;
    }

    GameDestory(newGame);
    PrintResualt(testName, scenario, err);
}

static void TestGameDestroyGameNull(void)
{
    int err = 0;
    char *testName = "TestGameDestroy";
    char *scenario = "GameNull";

    GameDestory(NULL);
    PrintResualt(testName, scenario, err);
}

static void TestGameDestroyDoubleFree(void)
{
    int err = 0;
    char *testName = "TestGameDestroy";
    char *scenario = "DoubleFree";
    Game *newGame = GameCreate();

    GameDestory(newGame);
    GameDestory(newGame);

    PrintResualt(testName, scenario, err);
}

static void TestGamePlayGameNULL(void)
{
    int err = 0;
    char *testName = "TestGamePlay";
    char *scenario = "GameNULL";

    GamePlay(NULL);

    PrintResualt(testName, scenario, err);
}

static void TestGamePlayGame(void)
{
    int err = 0;
    char *testName = "TestGamePlay";
    char *scenario = "Game";
    Game *newGame = GameCreate();

    GamePlay(newGame);
    GameDestory(newGame);

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