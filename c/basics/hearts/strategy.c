#include "strategy.h"

Card PlayHighRankFirst(Table *_table , Hand *_hand, size_t _firstPlayer)
{
    Card firstCard = _table[_firstPlayer];
    Suit trickSuit = SUITS(firstCard);
    Card cardToPlay;

    if(trickSuit == HEART)
    {
        return HandExtrectMinCard(_hand, HEART);
    }
    
    cardToPlay = HandExtractMaxCard(_hand, trickSuit);
    while(cardToPlay == INVALID_CARD)
    {
        trickSuit = (trickSuit + 1) % NUM_OF_SUITS;
        cardToPlay = HandExtractMaxCard(_hand, trickSuit);
    }

    return cardToPlay;
}

Card PlayLowRankFirst(Table *_table , Hand *_hand, size_t _firstPlayer)
{
    Card firstCard = _table[_firstPlayer];
    Suit trickSuit = SUITS(firstCard);
    Card cardToPlay;

    if(trickSuit == HEART)
    {
        return HandExtrectMinCard(_hand, HEART);
    }
    
    cardToPlay = HandExtractMinCard(_hand, trickSuit);
    while(cardToPlay == INVALID_CARD)
    {
        trickSuit = (trickSuit + 1) % NUM_OF_SUITS;
        cardToPlay = HandExtractMinCard(_hand, trickSuit);
    }

    return cardToPlay;
}

