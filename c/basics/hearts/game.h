#ifndef __GAME_H__
#define __GAME_H__

#include <stddef.h>     /* size_t */
#include "heartsErr.h"
#include "player.h"

typedef struct Game Game;

/*
    the function create game

    output:
        pointer to game

    error:
        if failed, return NULL
*/
Game *GameCreate();
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
    3) check if the game is ended
    3) if we dont end the game, play next round

    input:
        game - pointer to game 

    output:
        ERR_HEARTS_OK - on sucsses

    error:
        ERR_HEARTS_ALLOCATION_FAILED - if dynamic allocation failed
*/
heartsErr GamePlay(Game *_game);
/*
    the function check if game was end
    (some of the player reach to 100 points)

    input:
        game - pointer to game 

    output:
        0 on failure
        !0 on sucsses

    error:
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
