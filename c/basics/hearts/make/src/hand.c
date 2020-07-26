#include <stddef.h> /* NULL   */
#include <stdlib.h> /* calloc */
#include "hand.h"
#include "card.h"
#include "vector.h"
#include "heap.h"

struct Hand
{
    Heap *m_hands[NUM_OF_SUITS];
    Vector *m_vectors[NUM_OF_SUITS];
};

Hand *HandCreate()
{
    size_t i = 0;

    Hand *newHand = (Hand *)calloc(sizeof(Hand) ,sizeof(Hand));
    if(newHand == NULL)
    {
        return NULL;
    }

    for(; i < NUM_OF_SUITS; ++i)
    {
        newHand->m_vectors[i] = VectorCreate(NUM_OF_RANKS, 1);
        newHand->m_hands[i] = HeapBuild(newHand->m_vectors[i]);
        if(newHand->m_hands == NULL)
        {
            for(; i > 0; --i)
            {
                VectorDestroy(newHand->m_vectors[i]);
                HeapDestroy(newHand->m_hands[i]);
            }

            free(newHand);
            return NULL;
        }
    }

    return newHand;
}

void HandDestroy(Hand *_hand)
{
	size_t i = 0;
    
	if(_hand != NULL)
	{
		for(; i < NUM_OF_SUITS; ++i)
		{
			HeapDestroy(_hand->m_hands[i]);
            VectorDestroy(_hand->m_vectors[i]);
		}

        free(_hand);
	}
}

void HandAddCard(Hand *_hand, Card _card)
{
    HeapInsert(_hand->m_hands[SUITS(_card)] , _card);
}

Card HandExtractMaxCard(Hand *_hand, Suit _suit)
{
    int card;
    HeapExtractMax(_hand->m_hands[_suit], &card);
    return (Card)(card);
}

