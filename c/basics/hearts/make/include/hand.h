#ifndef __HAND_H__
#define __HAND_H__

#include "card.h"
#include "heartsErr.h"

/* --------------------------- */
/*		MODULE: hand

This module handles the entity of
a hand in a cards game.
Actions:

	Owner: Maor Alankri
	Created: 2.12.19.
	Last modified: 4.2.19.	   */
/* --------------------------- */
typedef struct Hand Hand;

/*
Creates dynamic allocation of Hand.
Output:
	A pointer to Hand.
Errors:
	NULL - If the dynamic allocation faild.
*/
Hand *HandCreate();

/*
Free dynamic allocation of hand.

Input:
	_hand - A pointer to _hand.
*/
void HandDestroy(Hand *_hand);

/*
Adds card to hand.

Input:
	_hand - A pointer to Hand.
	_card - The card we want to add to hand.

Output:
	status. If succeded returns ERR_OK.

Errors:
	ERR_NOT_INITIALIZED - If _hand NULL.
*/
void HandAddCard(Hand *_hand, Card _card);

/*
Takes out the highest card in hand from type suit and inserts it in card.

Input:
	_hand - A pointer to Hand.
	_card - A pointer to Card.
	_suit - The suit of the card we want.

Output:
	status. If succeded returns ERR_OK.

Errors:
	ERR_NOT_INITIALIZED - If hand or card NULL.
*/
Card HandExtractMaxCard(Hand *_hand, Suit _suit);

#endif/*__Hand_H__*/
