#ifndef __GAME_H__
#define __GAME_H__

#include "heartErr.h"
#include "player.h"

typedef struct Game Game;

struct Game
{
    Player **playresArr;
    Score *scoreTable;
    Dack *dack;
};

/*
    the function create game

    input:
        game - pointer to game 

    output:
        HeartsErr

    error:
        ERR_OK - on sucsses
        ERR_NOT_INISILIZE - if game is NULL
*/
Game *GameCreate(char **_Players_name);
/*
    the function destory game

    input:
        game - pointer to game

    the funtion free all dynamic allocatins
*/    
void GameDestory(Game *_game);
/*
    the function play game by rounds:

    1) create round
    2) play round
    3)update resualt
    3) if we dont end the game, play next round

    input:
        game - pointer to game 

    output:
        HeartsErr

    error:
        ERR_OK - on sucsses
        ERR_NOT_INISILIZE - if game is NULL
*/
HeartsErr GamePlay(Game *_game);
/*
    the function check if game was end
    (some of the player reach to 100 points)

    input:
        game - pointer to game 

    output:
        0 on failure
        !0 on sucsses

    error:
        if game is NULL return failure
*/
int IsGameEnd(Game *_game);
/*
    the function print game resualt

    input:
        game - pointer to game 

    output:
       
    error:  

*/
void PrintGameResualt(Game *_game);

#endif /* __GAME_H__*/


/* pseoudo code */

Flow:
{
    GetUserInput();
    GameCreate();
    GamePlay();
    PrintGameResualt();
    GameDestroy();
}

GamePlay Flow:
{
    while(!IsGameEnd())
    {
        CreateRound();
        PlayRound();
        UpdateScore();
    }
}