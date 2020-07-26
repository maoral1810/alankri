#ifndef __TRICK_H__
#define __TRICK_H__

#include "player.h" 
#include "table.h"
#include "heartsErr.h"

size_t TrickPlay(Player **_players, int *_losser, Table *_table, 
                 size_t _beginner, size_t _numOfPlayers);

#endif /* __TRICK_H__*/

