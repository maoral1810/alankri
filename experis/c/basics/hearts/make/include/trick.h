#ifndef __TRICK_H__
#define __TRICK_H__

#include "player.h" 
#include "heartErr.h"

typedef struct Trick Trick;
typedef Card *Table;

struct Trick
{
    Card trickTable[4];
    size_t tricksScore;
};

/* 

*/
Trick *TrickCreate(Player **_players);

void TrickDestory(Trick *_trick);

heartErr TrickPlay(Trick *_trick); 

Player *TrickCalcLosser(Trick *_trick);

void TrickUpdateScore(table?);




#endif /* __TRICK_H__*/


Play Flow:
{
    CreateTable();
    playFirstPlayer();

    { X (num Of Players - 1)
        PlayCard();/* who is the responsible */
    }

    CalcLosser();
    UpdateTableScore();
}