#include <stdlib.h> /* malloc, free */
#include "game.h" /* game Api */
#include "round.h"

#define MAX_PLAYERS 4

struct Game
{
    Player **m_players;
    size_t m_numOfPlayers;
};

Game *GameCreate()
{
    size_t numOfPlayers;
    char **playersNames;
    Strategy *playerStrategy;
    size_t i;
    Game *newGame;

    UIStartGame(&numOfPlayers, &playersNames, &playerStrategy);

    newGame = (Game *)malloc(sizeof(Game) * numOfPlayers);
    if(newGame == NULL)
    {
        return NULL;
    }

    for(i = 0; i < numOfPlayers; ++i)
    {
        newGame->m_players[i] =  PlayerCreate(playersNames[i], playerStrategy[i]);
        if(newGame->m_players[i] == NULL)
        {
            free(playersNames);
            free(playerStrategy);
            for(;i > 0; --i)
            {
                PlayerDestroy(newGame->m_players[i]);
            }
            free(newGame);

            return NULL;
        }
    }

    newGame->m_numOfPlayers = numOfPlayers;
    free(playersNames);
    free(playerStrategy);

    return newGame;
}

void GameDestory(Game *_game)
{
    size_t i;

    if(_game != NULL)
    {
        for(i = 0; i < _game->m_numOfPlayers; ++i)
        {
            PlayerDestroy(_game->m_players[i]);
        }

        free(_game);    
    }
}

heartsErr GamePlay(Game *_game)
{
    Round *newRound = RoundCreate(_game->m_players, _game->m_numOfPlayers);

    if(newRound == NULL)
    {
        return HEARTS_ALLOCATION_FAILED;
    }

    while (!IsGameEnd(_game))
    {
        RoundPlay(newRound);       
    }
    
    UIPrintGameResult(_game);

    return HEARTS_OK;
}

int IsGameEnd(Game *_game)
{
    size_t currentScore;
    size_t i;

    for(i = 0; i < _game->m_numOfPlayers; ++i)
    {
        PlayerGetScore(_game->m_players[i], &currentScore);
        if(currentScore >= 100)
        {
            return 1;
        }
    }

    return 0;
}

void PrintGameResualt(Game *_game)
{
    char *playersName[MAX_PLAYERS];
    size_t tableScore[MAX_PLAYERS];
    size_t i = 0;
    size_t score;

    for(; i < _game->m_numOfPlayers; ++i)
    {
        playersName[i] = PlayerGetName(_game->m_players[i]);
        PlayerGetScore(_game->m_players[i], &score);
        tableScore[i] = score;
    }

    UIPrintGameResult(playersName, tableScore, _game->m_numOfPlayers);
}