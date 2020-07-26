#ifndef __DECK_H__
#define __DECK_H__

#include "heartsErr.h"
#include "card.h"

typedef Card *Deck;

heartsErr Deckinitialized(Deck _deck);

Deck DeckCreate();

void DeckDestroy(Deck _deck);

int DeckDeal(Deck _deck);

void DeckPrint(Deck _deck);

#endif /*__DECK_H__*/
