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
    if( _hand == NULL || ERR_OK != HeapExtractMax(_hand->m_hands[_suit], &card))
    {
        return INVALID_CARD;
    }

    return (Card)(card);
}

Card HandExtrectMinCard(Hand *_hand, Suit _suit)
{
    size_t minIndex = 0;
    size_t i = 1;
    size_t vectorSize;
    Card minimumRank;
    int minData;
    int currentData;
    int nextData;

    VectorItemsNum(_hand->m_vectors[_suit], &vectorSize);
    VectorGet(_hand->m_vectors[_suit], 0, &minData);

    for(;i < vectorSize; ++i)
    {
        VectorGet(_hand->m_vectors[_suit], i, &currentData);

        if(currentData < minData)
        {
            minIndex = i;
            minData = currentData;
        }
    }

    minimumRank = minData;
    /* 1) take data from last element.
       2) set data of last element to minimum index.
       3) remove last element from vector.
       4) HeapBulid.
    */
    VectorGet(_hand->m_vectors[_suit], vectorSize - 1, &currentData);

    VectorSet(_hand->m_vectors[_suit], minIndex, currentData);
    VectorDelete(_hand->m_vectors[_suit], &currentData);

    HeapDestroy(_hand->m_hands[_suit]);
    _hand->m_hands[_suit] = HeapBuild(_hand->m_vectors[_suit]);

    return minimumRank;
}

void HandPrint(Hand * _hand)
{
    size_t j;

    if( _hand != NULL)
    {
        printf("HEART: ");
        HeapPrint(_hand->m_hands[0]);
        putchar('\n');

        printf("SPADE: ");
        HeapPrint(_hand->m_hands[1]);
        putchar('\n');

        printf("CLUB: ");
        HeapPrint(_hand->m_hands[2]);
        putchar('\n');
        
        printf("DIAMOND: ");
        HeapPrint(_hand->m_hands[3]);
        putchar('\n');
    }
}
