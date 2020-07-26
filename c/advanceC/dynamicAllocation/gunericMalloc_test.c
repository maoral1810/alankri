#include <stdio.h>
#include <stdlib.h>
#include "mu_test.h"
#include "gunericMalloc.h"

#define ARR_LENGTH(x) (sizeof(x) / sizeof(x[0]))

UNIT(TestCreatePool)
    void *newPool = CreatePool(20);

    ASSERT_THAT(NULL != newPool);

    DestroyPool(newPool);
END_UNIT

UNIT(TestGunericMallocValidSize)
    void *newPool = CreatePool(200);
    void *buffer = NULL;

    ASSERT_THAT(NULL != newPool);
    buffer = GunericMalloc(newPool, 100);

    ASSERT_THAT(buffer != NULL);
    DestroyPool(newPool);
END_UNIT

UNIT(TestGunericMallocInValidSize)
    void *newPool = CreatePool(2);
    void *buffer = NULL;

    ASSERT_THAT(NULL != newPool);
    buffer = GunericMalloc(NULL ,0);

    ASSERT_THAT(buffer == NULL);
    DestroyPool(newPool);
END_UNIT

UNIT(TestGunericMallocSizeZero)

    void *newPool = CreatePool(100);
    
    ASSERT_THAT(NULL != newPool);
    ASSERT_THAT(NULL == GunericMalloc(newPool, 0));

    DestroyPool(newPool);
END_UNIT

UNIT(TestGunericMallocNumOfElement1Alloc3buffers)
    void *newPool = CreatePool(100);
    void *buffer = NULL;

    ASSERT_THAT(NULL != newPool);

    buffer = GunericMalloc(newPool, 100);
    ASSERT_THAT(buffer != NULL);

    buffer = GunericMalloc(newPool, 100);
    ASSERT_THAT(buffer == NULL);

    buffer = GunericMalloc(newPool, 100);
    ASSERT_THAT(buffer == NULL);
    
    DestroyPool(newPool);
END_UNIT

UNIT(TestMyFreeNumOfElement3Alloc3Free2)

    void *newPool = CreatePool(100);
    void *buffer1 = NULL;
    void *buffer2 = NULL;
    void *buffer3 = NULL;

    ASSERT_THAT(NULL != newPool);

    buffer1 = GunericMalloc(newPool, 10);
    ASSERT_THAT(buffer1 != NULL);

    buffer2 = GunericMalloc(newPool, 50);
    ASSERT_THAT(buffer2 != NULL);

    buffer3 = GunericMalloc(newPool, 40);
    ASSERT_THAT(buffer3 == NULL);
    ASSERT_THAT(NULL != newPool);

    MyFree(buffer1, newPool);
    MyFree(buffer2, newPool);

    DestroyPool(newPool);

END_UNIT

UNIT(TestMyFreeNulls)
    void *newPool = CreatePool(10);
    void *buffer = NULL;

    MyFree(NULL, newPool);
    MyFree(&newPool, NULL);

    buffer = GunericMalloc(newPool ,10);
    ASSERT_THAT(buffer != NULL);

    DestroyPool(newPool);
END_UNIT

TEST_SUITE(GunericMalloc)
	TEST(TestCreatePool)
    TEST(TestGunericMallocValidSize)
    TEST(TestGunericMallocInValidSize)
    TEST(TestGunericMallocSizeZero)
    TEST(TestGunericMallocNumOfElement1Alloc3buffers)
    TEST(TestMyFreeNumOfElement3Alloc3Free2)
    TEST(TestMyFreeNulls)
END_SUITE

/* ----------------- static functions --------------------------------*/
