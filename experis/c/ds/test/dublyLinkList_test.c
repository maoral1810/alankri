#include <stddef.h> /* size_t */
#include <stdio.h>  /* printf */
#include "dublyLinkList.h"
#include "ADTDefs.h"
#include "colors.h" /* colors for printf */


static void TestListCreate(void);

static void TestListDestroyDubbleFree(void);
static void TestListDestroyNull(void);

static void TestListPushHeadNULL(void);
static void TestListPushHeadThreeItems(void);

static void TestListPushTailNULL(void);
static void TestListPushTailThreeItems(void);

static void TestListPopHeadNULLs(void);
static void TestListPopHeadFillAndCheck(void); /* fill element from tail,pop and check item */

static void TestListPopHeadNULLs(void);
static void TestListPopHeadFillAndCheck(void); 

static void TestListCountItemsNULLList(void);
static void TestListCountItemsEmptyList(void);
static void TestListCountItemsThreeItems(void);

static void TestListIsEmptyEmptyList(void);
static void TestListIsEmptyNotEmptyList(void);



static void PrintResualt(char *_testName, char *_scenario , int err);


int main(void)
{
    TestListCreate();
    TestListDestroyDubbleFree();
    TestListDestroyNull();
    TestListPushHeadNULL();
    TestListPushHeadThreeItems();
    TestListPushTailNULL();
    TestListPopHeadNULLs();
    TestListPushTailThreeItems();
    TestListPopHeadFillAndCheck(); 
    TestListCountItemsNULLList();
    TestListCountItemsEmptyList();
    TestListCountItemsThreeItems();
    TestListIsEmptyEmptyList();
    /* TestListIsEmptyNotEmptyList();  */ /* TODO */

    return 0;
}

static void TestListCreate(void)
{
    List *dlist = ListCreate();
    char *testNmae = "ListCreateAndDestroy";
    char *scenario = " " ;
    int err = 0;

    if(NULL == dlist)
    {
        ++err;
    }

    ListDestroy(dlist);

    PrintResualt(testNmae, scenario, err);
}

static void TestListDestroyDubbleFree(void)
{
    List *dlist = ListCreate();
    char *testNmae = "ListDestroy";
    char *scenario = "DubbleFree";
    int err = 0;

    if(NULL == dlist)
    {
        ++err;
    }

    ListDestroy(dlist);
    ListDestroy(dlist);

    PrintResualt(testNmae, scenario, err);    
}

static void TestListDestroyNull(void)
{
    char *testNmae = "ListDestroy";
    char *scenario = "Null";
    int err = 0;

    ListDestroy(NULL);

    PrintResualt(testNmae, scenario, err);    
}

static void TestListPushHeadThreeItems(void)
{
    List *dlist = ListCreate();
    char *testNmae = "ListPushHead";
    char *scenario = "ThreeItems";
    int err = 0;

    if(NULL == dlist)
    {
        ++err;
    }

    if(ERR_OK != ListPushHead(dlist, 5))
    {
        ++err;
    }

    if(ERR_OK != ListPushHead(dlist, 6))
    {
        ++err;
    }
    
    if(ERR_OK != ListPushHead(dlist, 11))
    {
        ++err;
    }

    ListDestroy(dlist);

    PrintResualt(testNmae, scenario, err);   
}

static void TestListPushHeadNULL(void)
{
    char *testNmae = "ListPushHead";
    char *scenario = "NULL";
    int err = 0;


    if(ERR_NOT_INITIALZED != ListPushHead(NULL, 1))
    {
        ++err;
    }

    PrintResualt(testNmae, scenario, err); 
}


static void TestListPushTailNULL(void)
{
    char *testNmae = "ListPushTail";
    char *scenario = "NULL";
    int err = 0;


    if(ERR_NOT_INITIALZED != ListPushTail(NULL, 1))
    {
        ++err;
    }

    PrintResualt(testNmae, scenario, err); 
}
static void TestListPushTailThreeItems(void)
{
    List *dlist = ListCreate();
    char *testNmae = "ListPushTail";
    char *scenario = "ThreeItems";
    int err = 0;

    if(NULL == dlist)
    {
        ++err;
    }

    if(ERR_OK != ListPushTail(dlist, 5))
    {
        ++err;
    }

    if(ERR_OK != ListPushTail(dlist, 6))
    {
        ++err;
    }
    
    if(ERR_OK != ListPushTail(dlist, 11))
    {
        ++err;
    }

    ListDestroy(dlist);

    PrintResualt(testNmae, scenario, err);  
}

static void TestListPopHeadNULLs(void)
{
    char *testNmae = "ListPopHead";
    char *scenario = "NULL";
    int err = 0;

    if(ERR_NOT_INITIALZED != ListPopHead(NULL, NULL))
    {
        ++err;
    }

    PrintResualt(testNmae, scenario, err); 
}

static void TestListPopHeadFillAndCheck(void)
{
    List *dlist = ListCreate();
    int data[] = {1,2,3,4,5,6};
    char *testNmae = "ListPopHead";
    char *scenario = "FillAndCheck";
    size_t size = sizeof(data) / sizeof(data[0]);
    size_t i = 0;
    int item = -1;
    int err = 0;

    if(NULL == dlist)
    {
        ++err;
    }
    
    /* fill list by pusing to head */
    for(;i < size; ++i)
    {
        if(ERR_OK != ListPushHead(dlist, data[i]))
        {
            ++err;
        }
    }

    for(i = 0; i < size; ++i)
    {
        if(ERR_OK != ListPopHead(dlist, &item))
        {
            
            if(item != data[size - i - 1])
            {
                ++err;
            }
        }
    }

    ListDestroy(dlist);

    PrintResualt(testNmae, scenario, err);  
}
static void TestListCountItemsNULLList(void)
{
    char *testNmae = "ListCountItems";
    char *scenario = "NULLList";
    int err = 0;

    if(ListCountItems(NULL) != 0)
    {
        ++err;
    }

    PrintResualt(testNmae, scenario, err);  
}
static void TestListCountItemsEmptyList(void)
{
    List *dlist = ListCreate();
    char *testNmae = "ListCountItems";
    char *scenario = "EmptyList";
    int err = 0;

    if(NULL == dlist)
    {
        ++err;
    }

    if(ListCountItems(dlist) != 0)
    {
        ++err;
    }

    ListDestroy(dlist);

    PrintResualt(testNmae, scenario, err); 

}

static void TestListCountItemsThreeItems(void)
{
    List *dlist = ListCreate();
    char *testNmae = "ListCountItems";
    char *scenario = "ThreeItems";
    int err = 0;

    if(NULL == dlist)
    {
        ++err;
    }

    if(ERR_OK != ListPushHead(dlist, 5))
    {
        ++err;
    }

    if(ERR_OK != ListPushHead(dlist, 6))
    {
        ++err;
    }
    
    if(ERR_OK != ListPushHead(dlist, 11))
    {
        ++err;
    }

    if(3 != ListCountItems(dlist)) 
    {
        ++err;
    }
    
    ListDestroy(dlist);

    PrintResualt(testNmae, scenario, err);       
}

static void TestListIsEmptyEmptyList(void)
{
    List *dlist = ListCreate();
    char *testNmae = "ListIsEmpty";
    char *scenario = "EmptyList";
    int err = 0;


    if (!ListIsEmpty(dlist))
    {
        ++err;
    }

    ListDestroy(dlist);

    PrintResualt(testNmae, scenario, err);     
}

static void TestListIsEmptyNotEmptyList(void)
{
    List *dlist = ListCreate();
    char *testNmae = "ListIsEmpty";
    char *scenario = "NotEmptyList";
    int err = 0;

    ListPushHead(dlist , 55);

    if (ListIsEmpty(dlist))
    {
        ++err;
    }

    ListDestroy(dlist);

    PrintResualt(testNmae, scenario, err);  
}


static void PrintResualt(char *_testName, char *_scenario , int err)
{
    if(err)
    {
        printf(BOLDCYAN"%s"BOLDYELLOW":%s: "BOLDRED"FAIL!\n"RESET,
        _testName, _scenario); 
    }
    else
    {
        printf(BOLDCYAN"%s"BOLDYELLOW":%s: "BOLDGREEN"SUCSSES \n"RESET,_testName, _scenario);
    }
}