#include <stddef.h>  /* size_t       */
#include <stdio.h>   /* printf       */
#include <stdlib.h>  /* malloc, free */
#include "dllist.h"  /* dllist API   */
#include "listfunctions.h"
#include "colors.h"  /* colors       */

#define ARR_LENGTH(x) (sizeof(x) / sizeof(x[0]))

static void PrintResualt(char *_testName, char *_scenario, int err);
static void ElementDestroy(void *_element);
static int PrintList(void* _element, void* _context);
static int FindElement(void* _element, void* _context);
static int IsSmaller(void* _x, void* _y);

static void TestListCreate(void);

static void TestListDestroyDubbleFree(void);
static void TestListDestroyListNull(void);
static void TestListDestroyListDynamicAllocation(void);

static void TestListPushHeadListNULL(void);
static void TestListPushHeadItemNULL(void);
static void TestListPushHeadThreeItems(void);

static void TestListPushTailListNULL(void);
static void TestListPushTailItemNULL(void);
static void TestListPushTailThreeItems(void);

static void TestListPopHeadListNULL(void);
static void TestListPopHeadItemNULL(void);
static void TestListPopHeadEmptyList(void);
static void TestListPopHeadFillAndCheck(void);

static void TestListPopTailListNULL(void);
static void TestListPopTailItemNULL(void);
static void TestListPopTailEmptyList(void);
static void TestListPopTailFillAndCheck(void);

static void TestListSizeEmptyList(void);
static void TestListSizeListNULL(void);
static void TestListSizePushAndPopItems(void);

/* iterators test */
static void TestListItrBeginListNull(void);
static void TestListItrBeginEmptyList(void);

static void TestListItrEndListNull(void);
static void TestListItrEndEmptyList(void);

static void TestListItrEquals(void);

static void TestListItrNextWrongItr(void);
static void TestListItrNextAndGet(void);

static void TestListItrPrevWrongItr(void);
static void TestListItrPrevAndGet(void);

static void TestListItrSetNewHead(void);

static void TestListItrInsertBeforeEmptyList(void);
static void TestListItrInsertBefore1Element(void);

static void TestListItrRemove2Elements(void);

static void TestListItrForEachFunctionNULL(void);
static void TestListItrForEachEmptyList(void);
static void TestListItrForEachPrintList(void);

static void TestListItrFindFirstFunctionNULL(void);
static void TestListItrFindFirstEmptyList(void);
static void TestListItrFindFirstElementExists(void);
static void TestListItrFindFirstElementNotExists(void);

static void TestListItrSortFunctionNULL(void);
static void TestListItrSortListSorted(void);
static void TestListItrSortListNotSorted(void);

static void TestListItrCut(void);
static void TestListItrSplice(void);

int main(void)
{
    TestListCreate();

    TestListDestroyDubbleFree();
    TestListDestroyListNull();
    TestListDestroyListDynamicAllocation();

    TestListPushHeadListNULL();
    TestListPushHeadItemNULL();
    TestListPushHeadThreeItems();

    TestListPushTailListNULL();
    TestListPushTailItemNULL();
    TestListPushTailThreeItems();

    TestListPopHeadListNULL();
    TestListPopHeadItemNULL();
    TestListPopHeadEmptyList();
    TestListPopHeadFillAndCheck();

    TestListPopTailListNULL();
    TestListPopTailItemNULL();
    TestListPopTailEmptyList();
    TestListPopTailFillAndCheck();

    TestListSizeEmptyList();
    TestListSizeListNULL();
    TestListSizePushAndPopItems();
    /* iterators test */

    TestListItrBeginListNull();
    TestListItrBeginEmptyList();

    TestListItrEndListNull();
    TestListItrEndEmptyList();

    TestListItrEquals();

    TestListItrNextWrongItr();
    TestListItrNextAndGet();

    TestListItrPrevWrongItr();
    TestListItrPrevAndGet();

    TestListItrSetNewHead();

    TestListItrInsertBeforeEmptyList();
    TestListItrInsertBefore1Element();
    
    TestListItrRemove2Elements();

    TestListItrForEachFunctionNULL();
    TestListItrForEachEmptyList();
    TestListItrForEachPrintList();

    TestListItrFindFirstFunctionNULL();
    TestListItrFindFirstEmptyList();
    TestListItrFindFirstElementExists();
    TestListItrFindFirstElementNotExists();

    TestListItrSortFunctionNULL();
    TestListItrSortListSorted();
    TestListItrSortListNotSorted();

    TestListItrCut();
    TestListItrSplice();

    return 0;
}

static void TestListCreate(void)
{
    List *dlist = ListCreate();
    char *testNmae = "ListCreateAndDestroy";
    char *scenario = " ";
    int err = 0;

    if (NULL == dlist)
    {
        ++err;
    }

    ListDestroy(&dlist, NULL);

    PrintResualt(testNmae, scenario, err);
}

static void TestListDestroyDubbleFree(void)
{
    List *dlist = ListCreate();
    char *testNmae = "ListDestroy";
    char *scenario = "DubbleFree";
    int err = 0;

    if (NULL == dlist)
    {
        ++err;
    }

    ListDestroy(&dlist, NULL);
    ListDestroy(&dlist, NULL);

    PrintResualt(testNmae, scenario, err);
}

static void TestListDestroyListNull(void)
{
    char *testNmae = "ListDestroy";
    char *scenario = "ListNull";
    int err = 0;

    ListDestroy(NULL, NULL);

    PrintResualt(testNmae, scenario, err);
}

static void TestListDestroyListDynamicAllocation(void)
{
    char *testNmae = "ListDestroy";
    char *scenario = "DynamicAllocation";
    int err = 0;
    List *dlist = ListCreate();
    int toInsert = 7;
    int *data = (int *)malloc(sizeof(int *));

    if (data == NULL)
    {
        ListDestroy(&dlist, NULL);
        return;
    }

    data = &toInsert;
    ListPushHead(dlist, data);

    ListDestroy(&dlist, ElementDestroy);
    /*     free(data); */
    PrintResualt(testNmae, scenario, err);
}

static void TestListPushHeadListNULL(void)
{
    char *testNmae = "TestListPushHead";
    char *scenario = "ListNULL";
    int item = 6;
    int err = 0;

    if (ListPushHead(NULL, &item) != LIST_UNINITIALIZED_ERROR)
    {
        ++err;
    }

    PrintResualt(testNmae, scenario, err);
}

static void TestListPushHeadItemNULL(void)
{
    char *testNmae = "TestListPushHead";
    char *scenario = "ItemNULL";
    List *dlist = ListCreate();
    int err = 0;

    if (ListPushHead(dlist, NULL) != LIST_NULL_ELEMENT_ERROR)
    {
        ++err;
    }

    ListDestroy(&dlist, NULL);
    PrintResualt(testNmae, scenario, err);
}

static void TestListPushHeadThreeItems(void)
{
    char *testNmae = "TestListPushHead";
    char *scenario = "ThreeItems";
    List *dlist = ListCreate();
    int err = 0;
    int data[] = {4, 5, 4, 5};
    size_t size = ARR_LENGTH(data);
    size_t i;

    for (i = 0; i < size; ++i)
    {
        if (LIST_SUCCESS != ListPushHead(dlist, &data[i]))
        {
            ++err;
        }
    }

    ListDestroy(&dlist, NULL);
    PrintResualt(testNmae, scenario, err);
}

static void TestListPushTailListNULL(void)
{
    char *testNmae = "TestListPushTail";
    char *scenario = "ListNULL";
    int item = 6;
    int err = 0;

    if (ListPushTail(NULL, &item) != LIST_UNINITIALIZED_ERROR)
    {
        ++err;
    }

    PrintResualt(testNmae, scenario, err);
}

static void TestListPushTailItemNULL(void)
{
    char *testNmae = "TestListPushTail";
    char *scenario = "ItemNULL";
    List *dlist = ListCreate();
    int err = 0;

    if (ListPushTail(dlist, NULL) != LIST_NULL_ELEMENT_ERROR)
    {
        ++err;
    }

    ListDestroy(&dlist, NULL);
    PrintResualt(testNmae, scenario, err);
}

static void TestListPushTailThreeItems(void)
{
    char *testNmae = "TestListPushTail";
    char *scenario = "ThreeItems";
    List *dlist = ListCreate();
    int err = 0;
    int data[] = {4, 5, 4, 5};
    size_t size = ARR_LENGTH(data);
    size_t i;

    for (i = 0; i < size; ++i)
    {
        if (LIST_SUCCESS != ListPushTail(dlist, &data[i]))
        {
            ++err;
        }
    }

    ListDestroy(&dlist, NULL);
    PrintResualt(testNmae, scenario, err);
}

static void TestListPopHeadListNULL(void)
{
    char *testNmae = "TestListPopHead";
    char *scenario = "ListNULL";
    void *item;
    int err = 0;

    if (ListPopHead(NULL, &item) != LIST_UNINITIALIZED_ERROR)
    {
        ++err;
    }

    PrintResualt(testNmae, scenario, err);
}

static void TestListPopHeadItemNULL(void)
{
    char *testNmae = "TestListPopHead";
    char *scenario = "ItemNULL";
    List *dlist = ListCreate();
    int err = 0;

    if (ListPopHead(dlist, NULL) != LIST_UNINITIALIZED_ERROR)
    {
        ++err;
    }

    ListDestroy(&dlist, NULL);
    PrintResualt(testNmae, scenario, err);
}

static void TestListPopHeadEmptyList(void)
{
    char *testNmae = "TestListPopHead";
    char *scenario = "EmptyList";
    List *dlist = ListCreate();
    void *item;
    int err = 0;

    if (ListPopHead(dlist, &item) != LIST_UNDERFLOW)
    {
        ++err;
    }

    ListDestroy(&dlist, NULL);
    PrintResualt(testNmae, scenario, err);
}

static void TestListPopHeadFillAndCheck(void)
{
    char *testNmae = "TestListPopHead";
    char *scenario = "FillAndCheck";
    List *dlist = ListCreate();
    void *item;
    int err = 0;
    int data[] = {1, 2, 3, 4, 5, 6, 7};
    size_t size = ARR_LENGTH(data);
    size_t i;

    for (i = 0; i < size; ++i)
    {
        ListPushTail(dlist, &data[i]);
    }

    for (i = 0; i < size; ++i)
    {
        ListPopHead(dlist, &item);

        if (*(int *)item != data[i])
        {
            ++err;
        }
    }

    ListDestroy(&dlist, NULL);
    PrintResualt(testNmae, scenario, err);
}

static void TestListPopTailListNULL(void)
{
    char *testNmae = "TestListPopTail";
    char *scenario = "ListNULL";
    void *item;
    int err = 0;

    if (ListPopHead(NULL, &item) != LIST_UNINITIALIZED_ERROR)
    {
        ++err;
    }

    PrintResualt(testNmae, scenario, err);
}

static void TestListPopTailItemNULL(void)
{
    char *testNmae = "TestListPopTail";
    char *scenario = "ItemNULL";
    List *dlist = ListCreate();
    int err = 0;

    if (ListPopHead(dlist, NULL) != LIST_UNINITIALIZED_ERROR)
    {
        ++err;
    }

    ListDestroy(&dlist, NULL);
    PrintResualt(testNmae, scenario, err);
}

static void TestListPopTailEmptyList(void)
{
    char *testNmae = "TestListPopTail";
    char *scenario = "EmptyList";
    List *dlist = ListCreate();
    void *item;
    int err = 0;

    if (ListPopHead(dlist, &item) != LIST_UNDERFLOW)
    {
        ++err;
    }

    ListDestroy(&dlist, NULL);
    PrintResualt(testNmae, scenario, err);
}

static void TestListPopTailFillAndCheck(void)
{
    char *testNmae = "TestListPopTail";
    char *scenario = "FillAndCheck";
    List *dlist = ListCreate();
    void *item;
    int err = 0;
    int data[] = {1, 2, 3, 4, 5, 6, 7};
    size_t size = ARR_LENGTH(data);
    size_t i;

    for (i = 0; i < size; ++i)
    {
        ListPushHead(dlist, &data[i]);
    }

    for (i = 0; i < size; ++i)
    {
        ListPopTail(dlist, &item);
        if (*(int *)item != data[i])
        {
            ++err;
        }
    }

    ListDestroy(&dlist, NULL);
    PrintResualt(testNmae, scenario, err);
}

static void TestListSizeListNULL(void)
{
    char *testNmae = "TestListSize";
    char *scenario = "ListNULL";
    int err = 0;

    if (ListSize(NULL) != 0)
    {
        ++err;
    }

    PrintResualt(testNmae, scenario, err);
}

static void TestListSizeEmptyList(void)
{
    char *testNmae = "TestListSize";
    char *scenario = "EmptyList";
    int err = 0;
    List *dlist = ListCreate();

    if (ListSize(dlist) != 0)
    {
        ++err;
    }

    ListDestroy(&dlist, NULL);
    PrintResualt(testNmae, scenario, err);
}

static void TestListSizePushAndPopItems(void)
{
    char *testNmae = "TestListSize";
    char *scenario = "PushAndPopItems";
    int err = 0;
    int data[] = {1, 2, 3, 4, 5, 6, 7};
    size_t size = ARR_LENGTH(data);
    size_t i;
    void *item;
    List *dlist = ListCreate();

    for (i = 0; i < size; ++i)
    {
        if (ListSize(dlist) != i)
        {
            ++err;
        }

        ListPushHead(dlist, &data[i]);
    }

    for (i = 0; i < size; ++i)
    {
        ListPopTail(dlist, &item);

        if (ListSize(dlist) != size - i - 1)
        {
            ++err;
        }
    }

    ListDestroy(&dlist, NULL);
    PrintResualt(testNmae, scenario, err);
}


/*------------------------------ itarators test -----------------------------*/
static void TestListItrBeginListNull(void)
{
    char *testNmae = "TestListItrBegin";
    char *scenario = "ListNull";
    int err = 0;

    if (!ListItrEquals(g_wrongIter,ListItrBegin(NULL)))
    {
        ++err;
    }

    PrintResualt(testNmae, scenario, err);
}

static void TestListItrBeginEmptyList(void)
{
    char *testNmae = "TestListItrBegin";
    char *scenario = "EmptyList";
    int err = 0;
    List *dlist = ListCreate();
    ListItr iter1;
    ListItr iter2;

    iter1 = ListItrBegin(dlist);
    iter2 = ListItrNext(iter1);

    if (iter1 != iter2)
    {
        ++err;
    }

    ListDestroy(&dlist, NULL);
    PrintResualt(testNmae, scenario, err);
}

static void TestListItrEndListNull(void)
{
    char *testNmae = "TestListItrEnd";
    char *scenario = "ListNull";
    int err = 0;

    if (!ListItrEquals(g_wrongIter,ListItrEnd(NULL)))
    {
        ++err;
    }

    PrintResualt(testNmae, scenario, err);
}

static void TestListItrEndEmptyList(void)
{
    char *testNmae = "TestListItrEnd";
    char *scenario = "EmptyList";
    int err = 0;
    List *dlist = ListCreate();
    ListItr iter1;
    ListItr iter2;

    iter1 = ListItrEnd(dlist);
    iter2 = ListItrNext(iter1);

    if (iter1 != iter2)
    {
        ++err;
    }

    ListDestroy(&dlist, NULL);
    PrintResualt(testNmae, scenario, err);
}

static void TestListItrEquals(void)
{
    char *testNmae = "TestListItrEquals";
    char *scenario = "";
    int err = 0;
    List *dlist = ListCreate();
    ListItr iter1;
    ListItr iter2;

    iter1 = ListItrEnd(dlist);
    iter2 = ListItrNext(iter1);

    if (!ListItrEquals(iter2, iter1))
    {
        ++err;
    }

    ListDestroy(&dlist, NULL);
    PrintResualt(testNmae, scenario, err);
}

static void TestListItrNextWrongItr(void)
{
    char *testNmae = "TestListItrNext";
    char *scenario = "WrongItr";
    int err = 0;

    ListItr itr = ListItrBegin(NULL);

    if(!ListItrEquals(g_wrongIter, ListItrNext(itr)))
    {
        ++err;
    }

    PrintResualt(testNmae, scenario, err);
}

static void TestListItrNextAndGet(void)
{
    char *testNmae = "TestListItrNextAndGet";
    char *scenario = "";
    int err = 0;
    int data[] = {4, 5, 6, 7};
    size_t size = ARR_LENGTH(data);
    size_t i;
    List *dlist = ListCreate();
    ListItr iter;
    ListItr endOfList;
    void *listData;

    for(i = 0; i < size; ++i)
    {
        ListPushTail(dlist, &data[i]);
    }

    endOfList = ListItrEnd(dlist);

    for(iter = ListItrBegin(dlist), i = 0; iter != endOfList; iter = ListItrNext(iter), ++i)
    {
        listData = ListItrGet(iter);
        if(*(int *)listData != data[i])
        {
            ++err;
        }
    }

    ListDestroy(&dlist, NULL);
    PrintResualt(testNmae, scenario, err);
}

static void TestListItrPrevWrongItr(void)
{
    char *testNmae = "TestListItrPrev";
    char *scenario = "WrongItr";
    int err = 0;

    ListItr itr = ListItrBegin(NULL);

    if(!ListItrEquals(g_wrongIter, ListItrPrev(itr)))
    {
        ++err;
    }

    PrintResualt(testNmae, scenario, err);
}

static void TestListItrPrevAndGet(void)
{
    char *testNmae = "TestListItrPrevAndGet";
    char *scenario = "";
    int err = 0;
    int data[] = {4, 5, 4, 5};
    size_t size = ARR_LENGTH(data);
    size_t i;
    List *dlist = ListCreate();
    ListItr iter;
    ListItr beginOfList;
    void *listData;

    for(i = 0; i < size; ++i)
    {
        ListPushTail(dlist, &data[i]);
    }

    beginOfList = ListItrBegin(dlist);

    for(iter = ListItrPrev(ListItrEnd(dlist)), i = size - 1; iter != beginOfList; iter = ListItrPrev(iter), --i)
    {
        listData = ListItrGet(iter);
        if(*(int *)listData != data[i])
        {
            ++err;
        }
    }

    ListDestroy(&dlist, NULL);
    PrintResualt(testNmae, scenario, err);
}

static void TestListItrSetNewHead(void)
{
    char *testNmae = "TestListItrSet";
    char *scenario = "NewHead";
    int err = 0;
    int data[] = {2, 55};
    List *dlist = ListCreate();
    ListItr iter;
    void *listData;

    ListPushHead(dlist, &data[0]);

    iter = ListItrBegin(dlist);
    listData = ListItrGet(iter);
    if(*(int *)listData != data[0])
    {
        ++err;
    }

    ListItrSet(iter, &data[1]);
    listData = ListItrGet(iter);
    if(*(int *)listData != data[1])
    {
        ++err;
    }    

    ListDestroy(&dlist, NULL);
    PrintResualt(testNmae, scenario, err);
}

static void TestListItrInsertBeforeEmptyList(void)
{
    char *testNmae = "TestListItrInsertBefore";
    char *scenario = "EmptyList";
    int err = 0;
    int data = 2;
    List *dlist = ListCreate();
    ListItr iter;

    iter = ListItrBegin(dlist);

    if(NULL != ListItrInsertBefore(iter, &data))
    {
        ++err;
    }

    ListDestroy(&dlist, NULL);
    PrintResualt(testNmae, scenario, err);
}

static void TestListItrInsertBefore1Element(void)
{
    char *testNmae = "TestListItrInsertBefore";
    char *scenario = "1Element";
    int err = 0;
    int data[] = {2, 55};
    List *dlist = ListCreate();
    ListItr iter;
    void *listData;

    ListPushHead(dlist, &data[1]);

    iter = ListItrBegin(dlist);

    if(NULL == ListItrInsertBefore(iter, &data[0]))
    {
        ++err;
    }

    iter = ListItrBegin(dlist);
    listData = ListItrGet(iter);

    if(*(int *)listData != data[0])
    {
        ++err;
    }   

    ListDestroy(&dlist, NULL);
    PrintResualt(testNmae, scenario, err);
}

static void TestListItrRemove2Elements(void)
{
    char *testNmae = "TestListItrRemove";
    char *scenario = "2Elements";
    int err = 0;
    int data[] = {2, 55};
    List *dlist = ListCreate();
    ListItr iter;
    
    ListPushHead(dlist, &data[1]);
    ListPushHead(dlist, &data[0]);

    iter = ListItrBegin(dlist);
    
    if(*(int *)ListItrRemove(iter) != data[0])
    {
        ++err;
    }

    iter = ListItrBegin(dlist);

    if(*(int *)ListItrRemove(iter) != data[1])
    {
        ++err;
    }      

    ListDestroy(&dlist, NULL);
    PrintResualt(testNmae, scenario, err);
}

static void TestListItrForEachFunctionNULL(void)
{
    char *testNmae = "TestListItrForEach";
    char *scenario = "FunctionNULL";
    int err = 0;
    int data[] = {2, 55};
    List *dlist = ListCreate();
    
    ListPushHead(dlist, &data[1]);
    ListPushHead(dlist, &data[0]);
    
    if(!ListItrEquals(ListItrBegin(dlist), ListItrForEach(
                                                            ListItrBegin(dlist), 
                                                            ListItrEnd(dlist), 
                                                            NULL, NULL)))
    {
        ++err;
    }

    ListDestroy(&dlist, NULL);
    PrintResualt(testNmae, scenario, err);
}

static void TestListItrForEachEmptyList(void)
{
    char *testNmae = "TestListItrForEach";
    char *scenario = "EmptyList";
    int err = 0;
    List *dlist = ListCreate();
    
    if(!ListItrEquals(ListItrEnd(dlist), ListItrForEach(
                                                            ListItrBegin(dlist), 
                                                            ListItrEnd(dlist), 
                                                            PrintList, NULL)))
    {
        ++err;
    }


    ListDestroy(&dlist, NULL);
    PrintResualt(testNmae, scenario, err);
}

static void TestListItrForEachPrintList(void)
{
    char *testNmae = "TestListItrForEach";
    char *scenario = "EmptyList";
    int err = 0;
    List *dlist = ListCreate();
    int data[] = {11,22,33,44,55,66,77,88,99};
    size_t size = ARR_LENGTH(data);
    size_t i;

    for(i = 0; i < size; ++i)
    {
        ListPushTail(dlist, &data[i]);
    }

    if(!ListItrEquals(ListItrEnd(dlist), ListItrForEach(
                                                            ListItrBegin(dlist), 
                                                            ListItrEnd(dlist), 
                                                            PrintList, NULL)))
    {
        ++err;
    }

    putchar('\n');
    ListDestroy(&dlist, NULL);
    PrintResualt(testNmae, scenario, err);
}

static void TestListItrFindFirstFunctionNULL(void)
{
    char *testNmae = "TestListItrFindFirst";
    char *scenario = "FunctionNULL";
    int err = 0;
    int data[] = {2, 55};
    List *dlist = ListCreate();
    
    ListPushHead(dlist, &data[1]);
    ListPushHead(dlist, &data[0]);
    
    if(ListItrEnd(dlist) != ListItrFindFirst(ListItrBegin(dlist), ListItrEnd(dlist), NULL, NULL))
    {
        ++err;
    }

    ListDestroy(&dlist, NULL);
    PrintResualt(testNmae, scenario, err);
}

static void TestListItrFindFirstEmptyList(void)
{
    char *testNmae = "TestListItrFindFirst";
    char *scenario = "EmptyList";
    int err = 0;
    List *dlist = ListCreate();
    
    if(!ListItrEquals(ListItrEnd(dlist),ListItrFindFirst(ListItrBegin(dlist), 
                                                        ListItrEnd(dlist), 
                                                        FindElement, NULL)))
    {
        ++err;
    }

    ListDestroy(&dlist, NULL);
    PrintResualt(testNmae, scenario, err);
}

static void TestListItrFindFirstElementExists(void)
{
    char *testNmae = "TestListItrFindFirst";
    char *scenario = "ElementExists";
    int err = 0;
    int data[] = {1,3,5,7,9};
    size_t size = ARR_LENGTH(data);
    size_t i;
    List *dlist = ListCreate();

    for(i = 0; i < size; ++i)
    {
        ListPushHead(dlist,&(data[i]));
    }

    if(!ListItrEquals(ListItrPrev(ListItrEnd(dlist)),ListItrFindFirst(
                                                        ListItrBegin(dlist), 
                                                        ListItrEnd(dlist), 
                                                        FindElement, &data[0])))
    {
        ++err;
    }

    ListDestroy(&dlist, NULL);
    PrintResualt(testNmae, scenario, err);
}

static void TestListItrFindFirstElementNotExists(void)
{
    char *testNmae = "TestListItrFindFirst";
    char *scenario = "ElementNotExists";
    int err = 0;
    int data[] = {1,3,5,7,9};
    size_t size = ARR_LENGTH(data);
    size_t i;
    List *dlist = ListCreate();
    int notExist = 10;

    for(i = 0; i < size; ++i)
    {
        ListPushHead(dlist,&(data[i]));
    }

    if(!ListItrEquals(ListItrEnd(dlist),ListItrFindFirst(
                                                        ListItrBegin(dlist), 
                                                        ListItrEnd(dlist), 
                                                        FindElement, &notExist)))
    {
        ++err;
    }

    ListDestroy(&dlist, NULL);
    PrintResualt(testNmae, scenario, err);
}

static void TestListItrSortFunctionNULL(void)
{
    char *testNmae = "TestListItrSort";
    char *scenario = "FunctionNULL";
    int err = 0;
    int data[] = {1,33,15,7,49};
    size_t size = ARR_LENGTH(data);
    size_t i;
    List *dlist = ListCreate();
    ListItr iter;

    for(i = 0; i < size; ++i)
    {
        ListPushHead(dlist,&(data[i]));
    }

    ListItrSort(ListItrBegin(dlist), ListItrEnd(dlist), NULL);

    for(iter = ListItrBegin(dlist), i = size -1; iter != ListItrEnd(dlist); 
                                                --i,iter = ListItrNext(iter))
    {
        if(!FindElement(ListItrGet(iter), &data[i]))
        {
            ++err;
        }
    }

    ListDestroy(&dlist, NULL);
    PrintResualt(testNmae, scenario, err);
}

static void TestListItrSortListSorted(void)
{
    char *testNmae = "TestListItrSort";
    char *scenario = "ListSorted";
    int err = 0;
    int data[] = {1,3,5,7,9};
    int expRes [] = {1,3,5,7,9};
    size_t size = ARR_LENGTH(data);
    size_t i;
    List *dlist = ListCreate();
    ListItr iter;

    for(i = 0; i < size; ++i)
    {
        ListPushTail(dlist,&(data[i]));
    }

    ListItrSort(ListItrBegin(dlist), ListItrEnd(dlist), IsSmaller);

    for(iter = ListItrBegin(dlist), i = 0; iter != ListItrEnd(dlist); 
                                                ++i,iter = ListItrNext(iter))
    {
        if(!FindElement(ListItrGet(iter), &expRes[i]))
        {
            ++err;
        }
    }

    ListDestroy(&dlist, NULL);
    PrintResualt(testNmae, scenario, err);
}

static void TestListItrSortListNotSorted(void)
{
    char *testNmae = "TestListItrSort";
    char *scenario = "ListNotSorted";
    int err = 0;
    int data[] = {10,3,565,78,9};
    int expRes [] = {3,9,10,78,565};
    size_t size = ARR_LENGTH(data);
    size_t i;
    List *dlist = ListCreate();
    ListItr iter;

    for(i = 0; i < size; ++i)
    {
        ListPushTail(dlist,&(data[i]));
    }

    printf(RED"dlist before sorting\n"RESET);
    ListItrForEach(ListItrBegin(dlist), ListItrEnd(dlist), PrintList,NULL);
    putchar('\n');

    ListItrSort(ListItrBegin(dlist), ListItrEnd(dlist), IsSmaller);
    
    printf(GREEN"dlist after sorting\n"RESET);
    ListItrForEach(ListItrBegin(dlist), ListItrEnd(dlist), PrintList,NULL);
    putchar('\n');
    
    for(iter = ListItrBegin(dlist), i = 0; iter != ListItrEnd(dlist); 
                                                ++i,iter = ListItrNext(iter))
    {
        if(!FindElement(ListItrGet(iter), &expRes[i]))
        {
            ++err;
        }
    }

    ListDestroy(&dlist, NULL);
    PrintResualt(testNmae, scenario, err);
}


static void TestListItrCut(void)
{
    char *testNmae = "TestListItrCut";
    char *scenario = "";
    int err = 0;
    int data[] = {1,2,3,4,5,6,7,8,9,10};
    size_t size = ARR_LENGTH(data);
    size_t i;
    List *dlist = ListCreate();
    ListItr newBegin;
    List *newList;

    for(i = 0; i < size; ++i)
    {
        ListPushTail(dlist,&(data[i]));
    }

    newBegin = ListItrBegin(dlist);
    
    for(i = 0; i < size / 2; ++i) /* forward to 5 */
    {
        newBegin = ListItrNext(newBegin); 
    }

    newList = ListItrCut(newBegin , ListItrPrev(ListItrEnd(dlist)));

    printf(GREEN"dlist: \n");
    ListItrForEach(ListItrBegin(dlist), ListItrEnd(dlist),PrintList,NULL);
    printf(YELLOW"new dlist:\n");
    ListItrForEach(ListItrBegin(newList), ListItrEnd(newList),PrintList,NULL);

    ListDestroy(&dlist, NULL);
    ListDestroy(&newList, NULL);

    PrintResualt(testNmae, scenario, err);
}

static void TestListItrSplice(void)
{
    char *testNmae = "TestListItrSplice";
    char *scenario = "";
    int err = 0;
    int data[] = {1,2,3,4,5,6,7,8,9,10};
    size_t size = ARR_LENGTH(data);
    size_t i;
    List *dlist = ListCreate();
    ListItr newBegin;

    for(i = 0; i < size; ++i)
    {
        ListPushTail(dlist,&(data[i]));
    }

    printf(RED"dlist before splice\n");
    ListItrForEach(ListItrBegin(dlist), ListItrEnd(dlist),PrintList,NULL);
    
    newBegin = ListItrBegin(dlist);
    
    for(i = 0; i < size / 2; ++i) /* forward to 5 */
    {
        newBegin = ListItrNext(newBegin);
    }

    newBegin = ListItrSplice(ListItrBegin(dlist),newBegin,ListItrPrev(ListItrEnd(dlist)));

    printf(GREEN"dlist after splice\n");
    ListItrForEach(ListItrBegin(dlist), ListItrEnd(dlist),PrintList,NULL);

    ListDestroy(&dlist, NULL);

    PrintResualt(testNmae, scenario, err);
}

/* --------------------helpful functions ----------------------------*/
static void PrintResualt(char *_testName, char *_scenario, int err)
{
    if (err)
    {
        printf(BOLDCYAN "%s" BOLDYELLOW ":%s: " BOLDRED "FAIL!\n" RESET,
               _testName, _scenario);
    }
    else
    {
        printf(BOLDCYAN "%s" BOLDYELLOW ":%s: " BOLDGREEN "SUCSSES \n" RESET, _testName, _scenario);
    }
}

static void ElementDestroy(void *_element)
{
    free(_element);
}

static int PrintList(void* _element, void* _context)
{
    if(_element != NULL)
    {
        printf("%d->",*(int *)_element);
        return TRUE;
    }

    return FALSE; 
}

static int FindElement(void* _element, void* _context)
{
    return (*(int *)_element == *(int *)_context);
}

static int IsSmaller(void* _x, void* _y)
{
    return (*(int *)_x > *(int *)_y);
}
