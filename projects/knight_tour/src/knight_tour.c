#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif /* _GNU_SOURCE */

#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc, free ,qsort */
#include <assert.h> /* assert */
#include <stdio.h>  /* printf */
#include <time.h>   /* time */
#include <string.h> /* memset */

/* colors*/
#define GREEN "\033[1;32m"
#define RED "\033[1;31m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define RESET "\033[0m" 


#include "knight_tour.h"
#include "intstack.h"

typedef enum status {SUCCESS, FAILURE, TIMEOUT} status_t;

#define POSITIONS_NUM (64ul)
#define TOURS_NUM (8)
#define TIME_RUN (600 * CLOCKS_PER_SEC)

#define IS_BIT_SET(board, pos) (( board & (1lu << pos) ) >> pos)
#define IS_BOARD_FULL(board) (board == 0xFFFFFFFFFFFFFFFF)
#define IS_ON_BOARD(row, col) ((0 <= row && 7 >= row) && (0 <= col && 7 >= col))
#define SET_BIT(board, pos) (board |= (1lu << pos))

typedef struct map_index_s
{
	short tours[TOURS_NUM];
	short tour_count;
} map_index_t;


static status_t KTour(size_t board, size_t pos, const map_index_t *tour_map,
	                        intstack_t *path, clock_t timer);
static int ArrengeMoves(const void *data1, const void *data2, void *arg);
static void PrintPath(intstack_t *stack);
static void MapInit(map_index_t *map);
static void SortMap(map_index_t *map);
static void PrintMap(map_index_t *map);

void KnightsTour(void)
{
	size_t pos = 0;
	intstack_t *path = IntStackCreate(POSITIONS_NUM);
	static map_index_t tour_map[POSITIONS_NUM] = {0};

  	memset(tour_map, 0, sizeof(map_index_t) * POSITIONS_NUM); /* zeroies map */
	MapInit(tour_map);
	PrintMap(tour_map);

	for (pos = 0; pos < POSITIONS_NUM; ++pos)
	{
		size_t board = 0;
		clock_t timer = clock();
		status_t k_status = KTour(board, pos, tour_map, path, timer);
		double time_to_run = (double)(clock() - timer) / (double)CLOCKS_PER_SEC;

		if (SUCCESS == k_status)
		{
			printf(GREEN"path %ld found in %f seconds\n"RESET, pos, time_to_run);
			PrintPath(path);
			printf("\n");
		}
		else
		{
			printf(RED"\n status for posison %ld is: %d , seconds %f\n"RESET
					, pos, k_status, time_to_run);
			printf("\n");
		}
	}

	IntStackDestroy(path);
}

void KTHeuristic(void)
{
	size_t pos = 0;
	intstack_t *path = IntStackCreate(POSITIONS_NUM);
	static map_index_t tour_map[POSITIONS_NUM] = { { {0}, 0 } };
	
  	memset(tour_map, 0, sizeof(map_index_t) * POSITIONS_NUM); /* zeroies map */
	MapInit(tour_map);
	SortMap(tour_map);
	printf(BLUE"\nmap after qsort\n"RESET);
	PrintMap(tour_map);

	for (pos = 0; pos < POSITIONS_NUM; ++pos)
	{
		size_t board = 0;
		clock_t timer = clock();
		status_t k_status = KTour(board, pos, tour_map, path, timer);
		double time_to_run = (double)(clock() - timer) / (double)CLOCKS_PER_SEC;

		if (SUCCESS == k_status)
		{
			printf(GREEN"path %ld found in %f seconds\n"RESET, pos, time_to_run);
			PrintPath(path);
			printf("\n");
		}
		else
		{
			printf(RED"\n status for posison %ld is: %d , seconds %f\n"RESET
					, pos, k_status, time_to_run);
			printf("\n");
		}
	}

	IntStackDestroy(path);
}

static status_t KTour(size_t board, size_t pos, const map_index_t *tour_map,
	                        intstack_t *path, clock_t timer)
{
    status_t status = FAILURE;
	short i = 0;

	if ((clock() - timer) > TIME_RUN)
	{
		return TIMEOUT;
	}

	if (IS_BOARD_FULL (board))
	{
		return SUCCESS;
	}

	if (IS_BIT_SET(board, pos))
	{
		return FAILURE;
	}

	SET_BIT(board, pos);

	for (i = 0; i < TOURS_NUM; ++i)
	{
		if ((FAILURE == status) && (-1 != tour_map[pos].tours[i]))
		{
			status = KTour(board, tour_map[pos].tours[i],
							tour_map, path, timer);
		}
	}

	if (SUCCESS == status)
	{
		IntStackPush(path, pos);

		return SUCCESS;
	}

	return status;

}

static void MapInit(map_index_t *map)
{
	size_t op = 0;
	size_t tour  = 0;
 
	for (op = 0; op < POSITIONS_NUM; ++op)
	{
		map[op].tour_count = 0;

		for (tour = 0; tour < TOURS_NUM; ++tour)
		{
			map[op].tours[tour] = -1;
		}
	}

	for (op = 0; op < POSITIONS_NUM; ++op)
	{
		short column = op % 8;
		short row = op / 8;
		tour = 0;

		if (IS_ON_BOARD(column + 1, row - 2))/* UP_RIGHT */
		{
			map[op].tours[tour] = column + 1 + (row - 2) * 8;
			++map[op].tour_count;
		}
		
		++tour;

		if (IS_ON_BOARD(column + 2, row - 1))/*RIGHT_UP*/
		{
			map[op].tours[tour] = column + 2 + (row - 1) * 8;
			++map[op].tour_count;
		}
		
		++tour;

		if (IS_ON_BOARD(column + 2, row + 1)) /*RIGHT_DOWN*/
		{
			map[op].tours[tour] = column + 2 + (row + 1) * 8;
			++map[op].tour_count;
		}

		++tour;

		if (IS_ON_BOARD(column + 1, row + 2))/*DOWN_RIGHT*/
		{
			map[op].tours[tour] = column + 1 + (row + 2) * 8;
			++map[op].tour_count;
		}

		++tour;
		
		if (IS_ON_BOARD(column - 1, row + 2))/*DOWN_LEFT*/
		{
			map[op].tours[tour] = column - 1 + (row + 2) * 8;
			++map[op].tour_count;
		}

		++tour;

		if (IS_ON_BOARD(column - 2, row + 1))/*LEFT_DOWN*/
		{
			map[op].tours[tour] = column - 2 + (row + 1) * 8;
			++map[op].tour_count;
		}

		++tour;

		if (IS_ON_BOARD(column - 2, row - 1))/*LEFT_UP*/
		{
			map[op].tours[tour] = column - 2 + (row - 1) * 8;
			++map[op].tour_count;
		}

		++tour;

		if (IS_ON_BOARD(column - 1, row - 2))/*UP_LEFT*/
		{
			map[op].tours[tour] = column - 1 + (row - 2) * 8;
			++map[op].tour_count;
		}
	}
}

/* Sorts positions with less tours first */
static int ArrengeMoves(const void *data1, const void *data2, void *arg)
{
	map_index_t *map = (map_index_t *)arg;

	if (-1 == *(short *)data1)
	{
		return 1;
	}

	if (-1 == *(short *)data2)
	{
		return -1;
	}

	return map[*(short *)data1].tour_count - map[*(short *)data2].tour_count;
}

static void SortMap(map_index_t *map)
{
	size_t op = 0;
	
	for (op = 0; op < POSITIONS_NUM; ++op)
	{
		qsort_r(map[op].tours, TOURS_NUM, sizeof(short), ArrengeMoves, map);
	}
}

static void PrintMap(map_index_t *map)
{
	size_t op = 0;
	size_t tour = 0;

	printf(BLUE"\nKnight Tour Map\n\n"RESET);

	for (op = 0; op < POSITIONS_NUM; ++op)
	{
		printf("valid positions for %lu :\n", op);
		{
			printf("\n");
			for (tour = 0; tour < TOURS_NUM; ++tour)
			{
				printf("%d ", map[op].tours[tour]);
			}
			printf("\n\n");
		}
	}
	printf("\n\n\n");
}

static void PrintPath(intstack_t *stack)
{
	short index = 0;

	printf(YELLOW"\npath from index %d:\n\n"RESET, IntStackPeek(stack));

	while (0 < IntStackSize(stack))
	{
		printf("-->%d, ", IntStackPeek(stack));

		IntStackPop(stack);
		++index;
	}

	printf("\n\n");
}
