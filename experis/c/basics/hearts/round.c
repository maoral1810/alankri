#include <stdlib.h> /* malloc, free */
#include "round.h"
#include "table.h"
#include "deck.h"
#include "trick.h"

static void RoundDealCards(Round *_round);

Round *RoundCreate(Player **_players, size_t _numOfPlayers)
{
    Round *newRound = (Round *)malloc(sizeof(Round));

    if(newRound == NULL)
    {
        return NULL;
    }

    newRound->scoreTable = (size_t *)calloc(sizeof(size_t), sizeof(size_t) * _numOfPlayers);
    if(newRound->scoreTable == NULL)
    {
        free(newRound);
        return NULL;
    }
    
    newRound->m_numOfPlayers = _numOfPlayers;
    newRound->m_numOfTricks = NUM_OF_RANKS;
    newRound->m_players = _players;
    newRound->m_beginner = INVLID_BEGINNER;

    return newRound;
}

void RoundDestory(Round *_round)
{
    size_t i = 0;

    if(_round != NULL)
    {
        for(; i < _round->m_numOfPlayers; ++i)
        {
            PlayerDestroy(_round->m_players[i]);
        }

        free(_round);
    }
}

heartsErr RoundPlay(Round *_round)
{
    Table roundTable[NUM_OF_SUITS] = {0};

    RoundDealCards(_round);

    while(!IsRoundEnd(_round))
    {
        TrickPlay(_round->m_players, &_round->m_beginner, roundTable, 
                  _round->m_beginner, _round->m_numOfPlayers);
        
        --_round->m_numOfTricks;
    }

    RoundUpdateScore(_round);
    RoundDestory(_round);

    return HEARTS_OK;
}

void RoundUpdateScore(Round *_round)
{
    size_t i = 0;

    for(; i < _round->m_numOfPlayers; ++i)
    {
        PlayerAddScore(_round->m_players[i], _round->scoreTable[i]);
    }
}

int IsRoundEnd(Round *_round)
{
    return (_round->m_numOfTricks == 0);
}

static void RoundDealCards(Round *_round)
{
    size_t i = 0;
    size_t j;
    Card toInsertCard;

    Deck *newDeck = DeckCreate();

    for(i = 0; i < _round->m_numOfPlayers; ++i)
    {
        for(j = 0; j < NUM_OF_RANKS; ++j)
        {
            toInsertCard = DeckDeal(newDeck);
            if(toInsertCard == GET_CARD(SPADE, TWO))
            {
                _round->m_beginner = i;
            }
            PlayerAddCard(_round->m_players[i], toInsertCard);
        }
    }

    DeckDestroy(newDeck);
}