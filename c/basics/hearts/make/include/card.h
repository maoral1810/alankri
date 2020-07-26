#ifndef __CARD_H__
#define __CARD_H__

#define NUM_OF_RANKS 13
#define NUM_OF_SUITS 4
#define SUITS(x)((Suit)(x) / NUM_OF_RANKS)

typedef int Card;

typedef enum
{
	TWO = 0,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	TEN,
	JACK,
	QUEEN,
	KING,
	ACE
} Rank;

typedef enum
{
	HEART = 0,
	SPADE,
	CLUB,
	DIAMOND
} Suit;

#endif /*__CARD_H__*/
