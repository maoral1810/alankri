#ifndef __ROUND_H__
#define __ROUND_H__

#include <stddef.h> /* size_t */
#include "player.h"
#include "hand.h"
#include "heartsErr.h"

#define INVLID_BEGINNER -1

typedef struct Round Round;

struct Round
{
    Player **m_players;
    size_t m_numOfPlayers;
    size_t m_numOfTricks;
    size_t *scoreTable;
    int m_beginner;
};

Round *RoundCreate(Player **_players, size_t _numOfPlayer);

void RoundDestory(Round *_round);

heartsErr RoundPlay(Round *_round);

void RoundUpdateScore(Round *_round);

int IsRoundEnd(Round *_round);

#endif /* __ROUND_H__*/


/* RoundPlay Flow:
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
} */