#include <stdlib.h> /* malloc, free */
#include <string.h> /* memset       */
#include <time.h>   /* time         */
#include "deck.h"

Deck *DeckCreate()
{
    Deck *newDeck = (Deck *)calloc(sizeof(Deck), 
                                   sizeof(Deck) * (NUM_OF_RANKS * NUM_OF_SUITS));
    return newDeck;
}

void DeckDestroy(Deck *_deck)
{
    if(_deck != NULL)
    {
        free( _deck);
    }
}

void Deckinitialized(Deck *_deck)
{
    _deck = memset(_deck, 0, sizeof(_deck));
}

Card DeckDeal(Deck *_deck)
{
    int i = 0;
    
    while(_deck[i] == 1)
    {
        srand(time(NULL));
        i = rand() % (NUM_OF_RANKS * NUM_OF_SUITS);
    }

    _deck[i] = 1;
    
    return i;
}