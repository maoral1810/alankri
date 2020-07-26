#ifndef __GENERIC_SORTS__
#define __GENERIC_SORTS__

#include <stddef.h> /* size_t */


typedef int (*LessFunc)(void *_x, void *_y);

void BubbleSort(void **_arr, size_t _size, LessFunc _lessFanc);
void ShakeSort(void **_arr, size_t _size, LessFunc _lessFanc);

#endif /* __GENERIC_SORTS__ */