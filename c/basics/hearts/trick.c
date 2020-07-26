#include "trick.h"

size_t TrickPlay(Player **_players, int *_losser, Table *_table, 
                 size_t _beginner, size_t _numOfPlayers)
{
    size_t i;
    size_t current = _beginner;

    for(i = 0; i < _numOfPlayers; ++i, current = (current + 1) % _numOfPlayers)
    {
        PlayerPlay(_players[current], _table);
    }

    return TableCalcLoser(_table, _numOfPlayers, _beginner, _losser);
}