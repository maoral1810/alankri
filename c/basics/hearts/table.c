#include <stdio.h> /* printf */
#include "table.h"
#include "ui.h"

#define NEXT_PLAYER(player, numOfPlayers)( (player + 1) % numOfPlayers)
static size_t CalcUserScore(const Table *_table, size_t _numOfPlayers);

void TableAddCard (Table* _table, size_t _playerIndex, Card _card)
{
    _table[_playerIndex] = _card;
}

size_t TableCalcLoser (const Table* _table, size_t _numOfPlayers, 
					   size_t _starterIndex, size_t *_loserIndex)
{
    size_t i  = NEXT_PLAYER(_starterIndex, _numOfPlayers);
    Card losserCard;
    size_t userScore = 0;
    Card suitOfTheRound = SUITS(_table[_starterIndex]);

    losserCard = _table[_starterIndex];
    *_loserIndex = i;

    for(; i != _starterIndex ; i = NEXT_PLAYER(i, _numOfPlayers))
    {
        if(SUITS(_table[i]) == suitOfTheRound && _table[i] > losserCard)
        {
            losserCard = _table[i];
            *_loserIndex = i;
        }
    }

    return CalcUserScore(_table, _numOfPlayers);
}

void TablePrint(const Table *_table, size_t _numOfPlayers)
{
    UIPrintTable(_table, _numOfPlayers);
    
/*     for(i = 0; i < _numOfPlayers; ++i)
    {
        printf("player %lu card: %d\n", i, _table[i]);
    } */
}

static size_t CalcUserScore(const Table *_table, size_t _numOfPlayers)
{
    size_t i = 0;
    size_t score = 0;

    for(i = 0; i < _numOfPlayers; ++i)
    {
        if(SUITS(_table[i]) == HEART)
        {
            ++score;
        }
        else if(_table[i] == GET_CARD(SPADE, QUEEN))
        {
            score += NUM_OF_RANKS;
        }
    }
    
    return score;
}



