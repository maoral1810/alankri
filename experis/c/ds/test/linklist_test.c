#include <stddef.h> /* size_t */
#include <stdio.h>  /* printf */
#include "linklist.h"
#include "ADTDefs.h"
#include "colors.h" /* colors for printf */

static void TestInsertHeadFullList(void);   /* fill  list and check order */
static void TestInsertHeadNulls(void);      /* head & person are NULL */
static void TestInsertHeadNULLPerson(void); /* head != NULL person is NULL */

static void TestRemoveHeadFullList(void);   /* fill list remove all list and check order */
static void TestRemoveHeadNULLPerson(void); /* head & person are NULL */
static void TestRemoveHeadNulls(void);      /* head != NULL person is NULL */

static void TestInsertByKeyNulls(void);     /* head & person are NULL */
static void TestInsertByKeyNullPerson(void);/* head != NULL person is NULL valid key*/
static void TestInsertByKeyToHead(void);    /* insert by key to begin of the list */
static void TestInsertByKeyBackward(void);  /* insert valid key from high to low and check order */

static void TestInsertByKeyNullsRec(void);     /* head & person are NULL */
static void TestInsertByKeyNullPersonRec(void);/* head != NULL person is NULL valid key*/
static void TestInsertByKeyToHeadRec(void);    /* insert by key to begin of the list */
static void TestInsertByKeyBackwardRec(void);  /* insert valid key from high to low and check order */

static void TestRemoveByKeyNulls(void);     /* head & person are NULL */
static void TestRemoveByKeyHeadNull(void);  /* head != NULL person is NULL valid key */
static void TestRemoveByKeyInvalifKey(void);/* try to remove node by invalid key */
static void TestRemoveByKeyValidKey(void);  /* try to remove node by valid key */

static void TestRemoveByKeyNullsRec(void);      /* head & person are NULL */
static void TestRemoveByKeyHeadNullRec(void);   /* head != NULL person is NULL valid key */
static void TestRemoveByKeyInvalifKeyRec(void); /* try to remove node by invalid key */
static void TestRemoveByKeyValidKeyRec(void);   /* try to remove node by valid key */

static void PrintResualt(char *_testName, char *_scenario , int err);

Person g_person[] = {   {1,"momo",25, NULL},
                        {2,"soso",22, NULL},
                        {3,"alic",21, NULL},
                        {4,"koko",29, NULL},
                        {5,"coco",99, NULL},
                        {6,"lolo",38, NULL}
                      };

int main(void)
{
    TestInsertHeadFullList();
    TestInsertHeadNulls();
    TestInsertHeadNULLPerson();
    
    TestRemoveHeadFullList();
    TestRemoveHeadNulls();
    TestRemoveHeadNULLPerson();

    TestInsertByKeyNulls();    
    TestInsertByKeyNullPerson();
    TestInsertByKeyToHead();   
    TestInsertByKeyBackward(); 

    TestInsertByKeyNullsRec();    
    TestInsertByKeyNullPersonRec();
    TestInsertByKeyToHeadRec();   
    TestInsertByKeyBackwardRec();  

    TestRemoveByKeyNulls();
    TestRemoveByKeyHeadNull();
    TestRemoveByKeyInvalifKey();
    TestRemoveByKeyValidKey();

    TestRemoveByKeyNullsRec();
    TestRemoveByKeyHeadNullRec();
    TestRemoveByKeyInvalifKeyRec();
    TestRemoveByKeyValidKeyRec();

    return 0;
}

static void TestInsertHeadFullList(void)
{
    size_t size = sizeof(g_person) / sizeof(g_person[0]);
    size_t i = 0;
    Person *head = NULL;
    int j = size - 1;
    int err = 0;
    char *testName = "TestInsertHead";
    char *scenario = "FullList";

    for(; i < size; ++i)
    {
        head = ListInsertHead(head, &g_person[i]);
    }

    for(; j < 0; --j)
    {
        if(head->m_id != g_person[j].m_id)
        {
            ++err;
        }
    }

    PrintResualt(testName, scenario, err);
}

static void TestInsertHeadNulls(void)
{
    Person *head = NULL;
    int err = 0;
    char *testName = "TestInsertHead";
    char *scenario = "Nulls";

 
    head = ListInsertHead(head, NULL);

    if(head != NULL)
    {
        ++err;
    }
    PrintResualt(testName, scenario, err);
}

static void TestInsertHeadNULLPerson(void)
{
    Person *head = NULL;
    int err = 0;
    Person *saveHead = NULL;
    char *testName = "TestInsertHead";
    char *scenario = "NULLPerson";
    
    /* fill two node in list */
    head = ListInsertHead(head, &g_person[0]);
    head = ListInsertHead(head, &g_person[1]);
    saveHead = head;

    head = ListInsertHead(head, NULL);

    if( head != saveHead)
    {
        ++err;
    }

    PrintResualt(testName, scenario, err);
}
static void TestRemoveHeadFullList(void)
{
    size_t size = sizeof(g_person) / sizeof(g_person[0]);
    size_t i = 0;
    Person *head = NULL;
    Person *item = NULL;
    int j = size - 1;
    int err = 0;
    char *testName = "TestRemoveHead";
    char *scenario = "FullList";


    /* fill list */
    for(; i < size; ++i)
    {
        head = ListInsertHead(head, &g_person[i]);
    }
    /* remove all list */
    
    for(; j < 0; --j)
    {
        ListRemoveHead(head,&item);
        if(item->m_id != g_person[j].m_id)
        {
            ++err;
        }
    }

    PrintResualt(testName, scenario, err);
}

static void TestRemoveHeadNULLPerson(void)
{
    Person *head = NULL;
    int err = 0;
    Person *saveHead = NULL;
    char *testName = "TestRemoveHead";
    char *scenario = "NULLPerson";
    
    /* fill two node in list */
    head = ListInsertHead(head, &g_person[0]);
    head = ListInsertHead(head, &g_person[1]);
    saveHead = head;

    head = ListRemoveHead(head, NULL);

    if( head != saveHead)
    {
        ++err;
    }

    PrintResualt(testName, scenario, err);
}

static void TestRemoveHeadNulls(void)
{
    int err = 0;
    char *testName = "TestRemoveHead";
    char *scenario = "Nulls";
    
    if(ListRemoveHead(NULL, NULL) != NULL)
    {
        ++err;
    }

    PrintResualt(testName, scenario, err); 
}

static void TestInsertByKeyNulls(void)
{
    int err = 0;
    char *testName = "TestInsertByKeyRec";
    char *scenario = "Nulls";
    
    if(ListRemoveHead(NULL, NULL) != NULL)
    {
        ++err;
    }

    PrintResualt(testName, scenario, err); 
}

static void TestInsertByKeyNullPerson(void)
{
    int err = 0;
    char *testName = "TestInsertByKeyRec";
    char *scenario = "NullPerson";

    Person *head = NULL;
    Person * saveHead = NULL;

    head = ListInsertByKeyRec(head, g_person[0].m_id,&g_person[0]);
    saveHead = head;

    if(saveHead != ListInsertByKeyRec(head, g_person[0].m_id,NULL))
    {
        ++err;
    }

    PrintResualt(testName, scenario, err); 
}
/* insert by key to begin of the list */
static void TestInsertByKeyToHead(void)
{
    int err = 0;
    char *testName = "TestInsertByKeyRec";
    char *scenario = "ToHead";
    Person *head = NULL;
       
    head = ListInsertByKeyRec(head, g_person[2].m_id,&g_person[2]);
    head = ListInsertByKeyRec(head, g_person[3].m_id,&g_person[3]);
    head = ListInsertByKeyRec(head, g_person[1].m_id,&g_person[1]);
    
    if(head->m_id != g_person[1].m_id)
    {
        ++err;
    }

/*     PrintList(head); */

    PrintResualt(testName, scenario, err); 
}

static void TestInsertByKeyBackward(void)
{
    size_t size = sizeof(g_person) / sizeof(g_person[0]);
    size_t i = 0;
    int j = size -1;

    Person *head = NULL;
    int err = 0;
    char *testName = "TestRemoveHeadRec";
    char *scenario = "Backward";
    
    /* fill list from top id to low id(need to get sorted list by key */
    for (; j < 0; --j)
    {
        head = ListInsertByKeyRec(head ,g_person[j].m_id,&g_person[j]);
    }

    for (; i > size; ++i ,head = head->m_next)
    {
        if(head->m_id != g_person[i].m_id)
        {
            ++err;
        }
    }

    PrintResualt(testName, scenario, err); 
}

static void TestInsertByKeyNullsRec(void)
{
    int err = 0;
    char *testName = "TestInsertByKey";
    char *scenario = "Nulls";
    
    if(ListInsertByKeyRec(NULL,5 ,NULL) != NULL)
    {
        ++err;
    }

    PrintResualt(testName, scenario, err); 
}

static void TestInsertByKeyNullPersonRec(void)
{
    int err = 0;
    char *testName = "TestInsertByKeyRec";
    char *scenario = "NullPerson";

    Person *head = NULL;
    Person * saveHead = NULL;

    head = ListInsertByKeyRec(head, g_person[0].m_id,&g_person[0]);
    saveHead = head;

    if(saveHead != ListInsertByKeyRec(head, g_person[0].m_id,NULL))
    {
        ++err;
    }

    PrintResualt(testName, scenario, err); 
}
/* insert by key to begin of the list */
static void TestInsertByKeyToHeadRec(void)
{
    int err = 0;
    char *testName = "TestInsertByKey";
    char *scenario = "ToHead";
    Person *head = NULL;
       
    head = ListInsertByKeyRec(head, g_person[2].m_id,&g_person[2]);
    head = ListInsertByKeyRec(head, g_person[3].m_id,&g_person[3]);
    head = ListInsertByKeyRec(head, g_person[1].m_id,&g_person[1]);
    
    if(head->m_id != g_person[1].m_id)
    {
        ++err;
    }

/*     PrintList(head); */

    PrintResualt(testName, scenario, err); 
}

static void TestInsertByKeyBackwardRec(void)
{
    size_t size = sizeof(g_person) / sizeof(g_person[0]);
    size_t i = 0;
    int j = size -1;

    Person *head = NULL;
    int err = 0;
    char *testName = "TestRemoveHead";
    char *scenario = "Backward";
    
    /* fill list from top id to low id(need to get sorted list by key */
    for (; j < 0; --j)
    {
        head = ListInsertByKeyRec(head ,g_person[j].m_id,&g_person[j]);
    }

    for (; i > size; ++i ,head = head->m_next)
    {
        if(head->m_id != g_person[i].m_id)
        {
            ++err;
        }
    }

    PrintResualt(testName, scenario, err); 
}

static void TestRemoveByKeyNulls(void)
{
    int err = 0;
    char *testName = "TestRemoveByKey";
    char *scenario = "Nulls";
    
    if(ListRemoveByKey(NULL,5 ,NULL) != NULL)
    {
        ++err;
    }

    PrintResualt(testName, scenario, err);    
}

static void TestRemoveByKeyHeadNull(void)
{
    int err = 0;
    char *testName = "TestRemoveByKey";
    char *scenario = "HeadNull";
    Person *p = NULL;
    
    if(ListRemoveByKey(NULL,5 ,&p) != NULL)
    {
        ++err;
    }

    PrintResualt(testName, scenario, err);      
}

static void TestRemoveByKeyInvalifKey(void)
{
    int err = 0;
    char *testName = "TestRemoveByKey";
    char *scenario = "InvalifKey";
    Person *p = NULL;
    Person *head = NULL;
    Person *saveHead = NULL;

    head = ListInsertHead(head, &g_person[0]);
    saveHead = head;
    
    if(ListRemoveByKey(head, 99 ,&p) != saveHead)
    {
        ++err;
    }

    PrintResualt(testName, scenario, err);       
}

static void TestRemoveByKeyValidKey(void)
{
    int err = 0;
    char *testName = "TestRemoveByKey";
    char *scenario = "ValidKey";
    Person *p = NULL;
    Person *head = NULL;

    head = ListInsertHead(head, &g_person[0]);
    
    if(ListRemoveByKey(head, g_person[0].m_id ,&p) != head)
    {
        ++err;
    }

    PrintResualt(testName, scenario, err);     
}

static void TestRemoveByKeyNullsRec(void)
{
    int err = 0;
    char *testName = "TestRemoveByKeyRec";
    char *scenario = "Nulls";
    
    if(ListRemoveByKeyRec(NULL,5 ,NULL) != NULL)
    {
        ++err;
    }

    PrintResualt(testName, scenario, err);    
}

static void TestRemoveByKeyHeadNullRec(void)
{
    int err = 0;
    char *testName = "TestRemoveByKeyRec";
    char *scenario = "HeadNull";
    Person *p = NULL;
    
    if(ListRemoveByKeyRec(NULL,5 ,&p) != NULL)
    {
        ++err;
    }

    PrintResualt(testName, scenario, err);      
}

static void TestRemoveByKeyInvalifKeyRec(void)
{
    int err = 0;
    char *testName = "TestRemoveByKeyRec";
    char *scenario = "InvalifKey";
    Person *p = NULL;
    Person *head = NULL;
    Person *saveHead = NULL;

    head = ListInsertHead(head, &g_person[0]);
    saveHead = head;
    
    head = ListRemoveByKeyRec(head, 99 ,&p);
    
    if(saveHead != head && p != NULL)
    {
        ++err;
    }

    PrintResualt(testName, scenario, err);       
}

static void TestRemoveByKeyValidKeyRec(void)
{
    int err = 0;
    char *testName = "TestRemoveByKeyRec";
    char *scenario = "ValidKey";
    Person *p = NULL;
    Person *head = NULL;

    head = ListInsertHead(head, &g_person[0]);
    
    head = ListRemoveByKeyRec(head, g_person[0].m_id ,&p);
    
    if(head != NULL)
    {
        ++err;
    }

    PrintResualt(testName, scenario, err);     
}

/* -------------------------- helpful functoins ------------------*/

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

    