#ifndef __MY_MALLOC__
#define __MY_MALLOC__

#include <stddef.h> /* size_t */

typedef struct Mdata Mdata;

void *CreateBuffer(size_t _numOfElements, size_t _sizeOfElement);
void DestroyBuffer(void *_buffer);
void *MyMalloc(void *_buffer);
void MyFree(void *_element, void *_buffer);

#endif /*__MY_MALLOC__ */

