#include <stdlib.h> /* malloc, free */
#include "player.h"
#include "hand.h"
#include "card.h"

#define NUM_OF_CARDS 13

struct Player
{
    char *m_name;
    Hand *m_hand;
    size_t m_score;
 	Strategy m_strategyFunc;
};

Player* PlayerCreate (char *_name, Strategy _strategyFunc)
{
    Player *newPlayer = NULL;

    newPlayer = (Player *)malloc(sizeof(Player));
    
    if(newPlayer == NULL)
    {
        return NULL;
    }

    newPlayer->m_name = _name; 
    newPlayer->m_hand = HandCreate();
    newPlayer->m_score = 0;
	newPlayer->m_strategyFunc = _strategyFunc;

    return newPlayer; 
}

void PlayerDestory(Player *_player)
{
    if(_player != NULL)
    {
        HandDestroy(_player->m_hand);
        PlayerDestory(_player);
    }
}

heartsErr PlayerAddCard (Player *_player, int _card)
{
    if(_player == NULL)
    {
        return HEARTS_NOT_INITIALIZED;
    }

    if(_card < TWO || _card > DIAMOND * ACE)
    {
        return HEARTS_WRONG_CARD;
    }

    HandAddCard(_player->m_hand,_card);

    return HEARTS_OK;
}

heartsErr PlayerAddScore (Player *_player, size_t _score)
{
    if(_player == NULL)
    {
        return HEARTS_NOT_INITIALIZED;
    }

    _player->m_score += _score;

    return HEARTS_OK;
}

heartsErr PlayerGetScore (const Player *_player, size_t *_score)
{
    if(_player == NULL || _score == NULL)
    {
        return HEARTS_NOT_INITIALIZED;
    }

    *_score = _player->m_score;

    return HEARTS_OK;
}

int PlayerPlay (Player *_player, const int *_table)
{
    if(_player == NULL || _table == NULL)
    {
        return HEARTS_NOT_INITIALIZED;
    }

	return (_player->m_strategyFunc)(_table, _player->m_hand);
}


