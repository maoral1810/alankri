#ifndef __DECK_H__
#define __DECK_H__

#include "heartsErr.h"
#include "card.h"

typedef Card Deck;

Deck *DeckCreate();

void DeckDestroy(Deck *_deck);

void Deckinitialized(Deck *_deck);

Card DeckDeal(Deck *_deck);

void DeckPrint(Deck *_deck);

#endif /*__DECK_H__*/
