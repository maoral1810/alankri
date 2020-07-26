#include <stdio.h>
#include <stdlib.h>
#include "mu_test.h"
#include "myMalloc.h"

#define ARR_LENGTH(x) (sizeof(x) / sizeof(x[0]))

UNIT(TestCreateBuffer)
    void *newBuffer = CreateBuffer(8, 20);

    ASSERT_THAT(NULL != newBuffer);

    DestroyBuffer(newBuffer);
END_UNIT

UNIT(TestMyMallocValidSize)
    void *newBuffer = CreateBuffer(1, 20);
    void *node = NULL;

    ASSERT_THAT(NULL != newBuffer);
    node = MyMalloc(newBuffer);

    ASSERT_THAT(node != NULL);
    DestroyBuffer(newBuffer);
END_UNIT

UNIT(TestMyMallocInValidSize)
    void *newBuffer = CreateBuffer(1,2);
    void *node = NULL;

    ASSERT_THAT(NULL != newBuffer);
    node = MyMalloc(newBuffer);

    ASSERT_THAT(node != NULL);
    DestroyBuffer(newBuffer);
END_UNIT

UNIT(TestMyMallocSizeZero)

    void *newBuffer = CreateBuffer(0,2);
    
    ASSERT_THAT(NULL == newBuffer);

    newBuffer = CreateBuffer(2,0);
    ASSERT_THAT(NULL == newBuffer);
    DestroyBuffer(newBuffer);
END_UNIT

UNIT(TestMyMallocNumOfElement1Alloc3Nodes)
    void *newBuffer = CreateBuffer(1,10);
    void *node = NULL;

    ASSERT_THAT(NULL != newBuffer);

    node = MyMalloc(newBuffer);
    ASSERT_THAT(node != NULL);

    node = MyMalloc(newBuffer);
    ASSERT_THAT(node == NULL);

    node = MyMalloc(newBuffer);
    ASSERT_THAT(node == NULL);
    
    DestroyBuffer(newBuffer);
END_UNIT

UNIT(TestMyFreeNumOfElement3Alloc3Free2)

    void *newBuffer = CreateBuffer(3,10);
    void *node1 = NULL;
    void *node2 = NULL;
    void *node3 = NULL;

    ASSERT_THAT(NULL != newBuffer);

    node1 = MyMalloc(newBuffer);
    ASSERT_THAT(node1 != NULL);

    node2 = MyMalloc(newBuffer);
    ASSERT_THAT(node2 != NULL);

    node3 = MyMalloc(newBuffer);
    ASSERT_THAT(node3 != NULL);
    ASSERT_THAT(NULL != newBuffer);

    MyFree(node1, newBuffer);
    MyFree(node2, newBuffer);

    DestroyBuffer(newBuffer);

END_UNIT

UNIT(TestMyFreeNulls)
    void *newBuffer = CreateBuffer(3,10);
    void *node = NULL;

    MyFree(NULL, newBuffer);
    MyFree(&newBuffer, NULL);

    node = MyMalloc(newBuffer);
    ASSERT_THAT(node != NULL);

    node = MyMalloc(newBuffer);
    ASSERT_THAT(node != NULL);

    node = MyMalloc(newBuffer);
    ASSERT_THAT(node != NULL);

    DestroyBuffer(newBuffer);
END_UNIT

TEST_SUITE(MyMalloc)
	TEST(TestCreateBuffer)
    TEST(TestMyMallocValidSize)
    TEST(TestMyMallocInValidSize)
    TEST(TestMyMallocSizeZero)
    TEST(TestMyMallocNumOfElement1Alloc3Nodes)
    TEST(TestMyFreeNumOfElement3Alloc3Free2)
    TEST(TestMyFreeNulls)
END_SUITE

/* ----------------- static functions --------------------------------*/
