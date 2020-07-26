#ifndef __STRATEGY_H__
#define __STRATEGY_H__

#include "hand.h"
#include "table.h"

typedef Card (*Strategy)(const Table *_table, Hand *_hand, size_t _firstPlayer);

Card PlayHighRankFirst(Table *_table , Hand *_hand, size_t _firstPlayer);

Card PlayLowRankFirst(Table *_table , Hand *_hand, size_t _firstPlayer);

/* Card PlayBeatMeIfYouCan(Table *_table , Hand *_hand, size_t _firstPlayer); */


#endif /* __STRATEGY_H__ */