#ifndef __PLAYER_H__
#define __PLAYER_H__

/* --------------------------- */
/*		MODULE: PLAYER

This module handles the entity of
a player in a cards game.
Actions: holding cards and score,
adding a card to hand, playing a
card according to a defined strategy,
and adding and getting score.
The player's hand is an array of vectors.

	Owner: Maor Alankri
	Created: 2.12.19.
	Last modified: 5.2.19.	   */
/* --------------------------- */

#include "heartsErr.h"
#include "card.h"
#include "hand.h"
#include "strategy.h"

typedef struct Player Player;

/* typedef card *(Startegy(Table *_table, Hand *_hand)); */

/*
This function creates a player.
The player's hand is an array of vectors.
Input:
		char* _name: the player's name.
					If NULL is passed, the function will create an AI player.
		Strategy _strategyFunc: a strategy function according to which
								the player will play.
Output:
		Pointer to Player.
Errors:
		If _strategyFunc is NULL -> NULL is returned (sidenote: or define a default strategy).
		If one of the allocations required within the Player fails -> NULL is returned.
*/
Player* PlayerCreate (char* _name, Strategy _strategyFunc);

/* TO BE COMPLETED.
This function destroyed a previously created player.
Input;
		Player* _player: pointer to Player.
Output:
		None.
Errors:
		None.
*/
void PlayerDestroy (Player* _player);

/*
This function adds a card to the player's hand.
Input:
		Player* _player: pointer to Player.
		int _card: card to be added.
Output:
		Status ERR_OK.
Errors:
		If _player is NULL -> ERR_NOT_INITIALIZED is returned,
		if _card is < 0 or >= MAX_NUM_OF_CARDS (52) -> ERR_WRONG_CARD is returned,
		if _card should be added to a suit which is already full -> ERR_FULL_SUIT is returned.
*/
heartsErr PlayerAddCard (Player* _player, Card _card);

/*
With this function, the player will provide a card to be played, according to the strategy
previously provided, and taking into consideration the state of the game's table of cards.
The card to be played is removed from the player's hand.
Input:
		Player* _player: pointer to Player.
		const Table* _table: the game's table of cards.
Output:
		Pointer to Card to be played.
Errors:
		If _player or _table are NULL -> NULL is returned,
		if player's hand is empty -> NULL is returned.
*/
int PlayerPlay (Player* _player, const int* _table);

/*
This function adds score to the player's total score.
Input:
		Player* _player: pointer to Player.
		size_t score: the score to be added.
Output:
		Status ERR_OK.
Errors:
		If _player is NULL -> ERR_NOT_INITIALIZED is returned.
*/
heartsErr PlayerAddScore (Player* _player, size_t _score);

/*
This function gets the player's current score.

	Input:
		_player - pointer to Player.
		_score 	- address where retrieved score will be stored.
	
	Output:
		Status ERR_OK.
	
	Errors:
		HEARTS_NOT_INITIALIZED - If _player or _score are NULL.
*/
heartsErr PlayerGetScore (const Player* _player, size_t* _score);

/*
	This function gets the player's name.

	Input:
		_player - pointer to Player.
	
	Output:
		player name( return NULL if the player is robot).
*/
char *PlayerGetName(const Player *_player);

void PrintPlayer(Player *_player);

#endif /* __PLAYER_H__ */
