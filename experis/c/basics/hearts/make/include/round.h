#ifndef __ROUND_H__
#define __ROUND_H__

#include <stddef.h> /* size_t */
#include "heartErr.h"

typedef struct Round Round;

struct Round
{
    size_t countTricks;

};

Round *RoundCreate();

void RoundDestory(Round *_round);

heartErr RoundPlay(Round *_round);

heartErr RoundUpdateScore(Player **_players, table);

int IsRoundEnd(Round *_round);

#endif /* __ROUND_H__*/


RoundPlay Flow:
{
    shuffleCard();
    DealCards();
    SortsHands();
    TrickCreate();
    
    while(!IsRoundEnd())
    {
        TrickPlay();
    }
    
    RoundUpdateScore();
    PrintScore();
    TrickDestory();        
}