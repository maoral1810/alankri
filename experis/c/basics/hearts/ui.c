#include "ui.h"
#include "colors.h"
#include "strategy.h"

heartsErr UIStartGame(size_t *_numOfPlayers, char **_playersNames, 
                      Strategy *_playerStrategy)
{
    size_t i;
    int strategeyFunc;
    printf(BOLDRED"<><><><><>    hello and welcome to Hearts game    <><><><><><><>\n" RESET);
    printf("please enter number of players (2-4)\n");
    scanf("%lu",_numOfPlayers);

    for(i = 0; i < *_numOfPlayers; ++i)
    {
        printf("please enter number of players\n");
        scnaf("%s",_playersNames[i]);
        
        printf("please enter the strategy for player\nenter 1 to highfirst\nenter 2 to lowfirst\n");
        scanf("%d",strategeyFunc);
        switch (strategeyFunc)
        {
        
        case 1:
            _playerStrategy[i] = PlayHighRankFirst;
            break;
        
        case 2:
            _playerStrategy[i] = PlayLowRankFirst;
            break;
        
        default:
            break;
        }
    }

    printf(BOLDGREEN"Game initialize---> let start play :) \n"RESET);
}

void UIPrintGameResualt(char **_playersNames, size_t *_tableScore, 
                        size_t _numOfPlayers)
{
    size_t i;

    printf(BOLDBLUE"Name:"RESET);

    for(i = 0; i < _numOfPlayers; ++i)
    {
        printf("%-15s",_playersNames[i]);
    }

    printf(BOLDYELLOW"Score:"RESET);

    for(i = 0; i < _numOfPlayers; ++i)
    {
        printf("%-15lu",_tableScore[i]);
    }
}


