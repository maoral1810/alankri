#ifndef __TABLE_H__
#define __TABLE_H__

/* --------------------------- */
/*		MODULE: TABLE

This module handles the entity of
a table of cards in a cards game.
Actions: adding a card to the table,
calculating the loser from the table.

	Owner: Maor Alankri
	Created: 2.12.19.
	Last modified: 7.12.19.	   */
/* --------------------------- */

#include <stddef.h> /* size_t */
#include "card.h"
#include "heartsErr.h"

typedef Card Table;

/*
This function adds a card to the table.
	Input:
		_table: 		pointer to table,
        _playerIndex: 	the index of the playing player.
        _card: 			card to be added to table.
	
	Output:
		Status HEARTS_OK.
	
	Errors:
		If _table is NULL -> HEARTS_NOT_INITIALIZED is returned,
		if _playerIndex is >= number of players -> HEARTS_WRONG_INDEX is returned,
        if _card is invalid (< 0 || >= MAX_NUM_OF_CARDS), -> HEARTS_WRONG_CARD is returned.
*/
void TableAddCard (Table* _table, size_t _playerIndex, Card _card);

/*
This function decides upon the loser at the loser and returns his index and calculated score.
	Input:
		Table* _table: pointer to table.
        size_t _score: score to be added to the loser.
        size_t* _loserIndex: address for storing the loser's index.
		size_t* _loserScore: address for storing the loser's score.
	
	Output:
		losserScore.
	
	Errors:
		If _table or _loserIndex are NULL -> HEARTS_NOT_INITIALIZED,
        if _playerIndex is >= number of players -> HEARTS_WRONG_INDEX is returned.
*/
size_t TableCalcLoser (const Table* _table, size_t _numOfPlayers, 
					   size_t _starterIndex, size_t *_loserIndex);
					   


void TablePrint(const Table *_table, size_t _numOfPlayers);

#endif /* __TABLE_H__ */
