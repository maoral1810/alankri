#ifndef __UI_H__
#define __UI_H__

#include <stddef.h> /* size_t */
#include "strategy.h"
#include "heartsErr.h"

/*
    the function start the game and collect infomation from user
    the function also  allocation the place for all inputs.

    input:
        _numOfPlayers   - pointer to number of players
        _playersNames   - pointer to arr of players names
        _playerStrategy - pointer to arr of Strategy

    output:
        HEARTS_OK -on sucsses
    
    error:
        HEARTS_ALLOCATION_FAILED - if one of the allocatin is failed
*/

heartsErr UIStartGame(size_t *_numOfPlayers, char **_playersNames, 
                      Strategy *_playerStrategy);
/*
    the function print game resualt

    input:
        _playersNames   - arr of names 
        _tableScore     - arr of scores
        _numOfPlayers   - number of players
*/
void UIPrintGameResualt(char **_playersNames, size_t *_tableScore, 
                        size_t _numOfPlayers);
/*
    the function print table

    input:
        _table        - arr of Cards 
        _numOfPlayers - number of players
*/
void UIPrintTable(int *_table, size_t _numOfPlayers);

/*
    the function print hand

    input:
        _cards        - arr of Cards 
        _numOfPlayers - number of players
*/
void UIPrintHand(int *_cards, size_t _numOfCards);

/*
    the function print Player

    input:
        _playerName - name of the player 
        _score      - score of the player
*/
void UIPrintPlayer(char *_playerName, size_t _score);

#endif /* __UI_H__ */