#ifndef __GUNERIC_MALLOC__
#define __GUNERIC_MALLOC__

#include <stddef.h> /* size_t */

typedef struct Mdata Mdata;

void *CreatePool(size_t _poolSize);
void DestroyPool(void *_pool);
void *GunericMalloc(void *_pool, size_t _bufferSize);
void MyFree(void *_buffer, void *_pool);

#endif /*__GUNERIC_MALLOC__ */