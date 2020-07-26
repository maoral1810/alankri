#include <stdio.h>  /* printf   */
#include <stdlib.h> /* free     */
#include "colors.h"
#include "bst.h"           /* bst API  */
#include "bsthelpFucntions.h" /* gets functions */

static void PrintResualt(char *_testName, char *_scenario, int err);

static void TestCreateTree(void);

static void TestTreeDestroyNULL(void);
static void TestTreeDestroyDoubleFree(void);

static void TestTreeInsertTreeNULL(void);
static void TestTreeInsertTreeSameData(void);
static void TestTreeInsertTreeTwoSides(void);
static void TestTreeInsertBigTree(void);
static void TestTreeInsertAfterDestroy(void);

static void TestTreeIsDataFoundDataNotExsist(void);
static void TestTreeIsDataFoundDataExsist(void);

static void TestTreePrint(void);

static void TestTreeIsTreeIsFullNULL(void);
static void TestTreeIsTreeIsFullFullTree(void);
static void TestTreeIsTreeIsFullNotFullTree(void);

static void TestAreSimilarTreeTree1NULL(void);
static void TestAreSimilarTreeTree2NULL(void);
static void TestAreSimilarTreeSimilar(void);
static void TestAreSimilarTreeNotSimilarLeft(void);
static void TestAreSimilarTreeNotSimilarRight(void);

static void TestIsPerfectTreeNULL(void);
static void TestIsPerfectTreeNotPerfect(void);
static void TestIsPerfectTreePerfect(void);


int main(void)
{
    TestCreateTree();

    TestTreeDestroyNULL();
    TestTreeDestroyDoubleFree();

    TestTreeInsertTreeNULL();
    TestTreeInsertTreeSameData();
    TestTreeInsertTreeTwoSides();
    TestTreeInsertBigTree();
    TestTreeInsertAfterDestroy();
    TestTreeIsDataFoundDataNotExsist();
    TestTreeIsDataFoundDataExsist();

    TestTreePrint();

    TestTreeIsTreeIsFullNULL();
    TestTreeIsTreeIsFullFullTree();
    TestTreeIsTreeIsFullNotFullTree();

    TestAreSimilarTreeTree1NULL();
    TestAreSimilarTreeTree2NULL();
    TestAreSimilarTreeSimilar();
    TestAreSimilarTreeNotSimilarLeft();
    TestAreSimilarTreeNotSimilarRight();

    TestIsPerfectTreeNULL();
    TestIsPerfectTreeNotPerfect();
    TestIsPerfectTreePerfect();

    return 0;
}

static void TestCreateTree(void)
{
    Tree *bst = NULL;
    int err = 0;
    char *testName = "TestCreateTree";
    char *scenario = "";

    bst = TreeCreate();

    if (NULL == bst)
    {
        ++err;
    }

    TreeDestroy(bst);
    bst = NULL;

    PrintResualt(testName, scenario, err);
}

static void TestTreeDestroyNULL(void)
{
    char *testName = "TreeDestroy";
    char *scenario = "NULL";

    TreeDestroy(NULL);

    PrintResualt(testName, scenario, 0);
}

static void TestTreeDestroyDoubleFree(void)
{
    Tree *bst = NULL;
    int err = 0;
    char *testName = "TreeDestroy";
    char *scenario = "DoubleFree";

    bst = TreeCreate();

    if (NULL == bst)
    {
        ++err;
    }

    TreeDestroy(bst);
    TreeDestroy(bst);
    bst = NULL;

    PrintResualt(testName, scenario, err);
}

static void TestTreeInsertTreeNULL(void)
{
    int err = 0;
    char *testName = "TreeInsert";
    char *scenario = "NULL";

    if (ERR_NOT_INITIALZED != TreeInsert(NULL, 0))
    {
        ++err;
    }

    PrintResualt(testName, scenario, err);
}

static void TestTreeInsertTreeSameData(void)
{
    Tree *bst = TreeCreate();
    int err = 0;
    char *testName = "TreeInsert";
    char *scenario = "SameData";

    if (ERR_OK != TreeInsert(bst, 1))
    {
        ++err;
    }

    if (ERR_DATA_EXSIST != TreeInsert(bst, 1))
    {
        ++err;
    }

    TreeDestroy(bst);

    PrintResualt(testName, scenario, err);
}

static void TestTreeInsertTreeTwoSides(void)
{
    Tree *bst = TreeCreate();
    int err = 0;
    char *testName = "TreeInsert";
    char *scenario = "TwoSides";
    Node *current = NULL;

    if (ERR_OK != TreeInsert(bst, 10))
    {
        ++err;
    }

    if (ERR_OK != TreeInsert(bst, 5))
    {
        ++err;
    }

    if (ERR_OK != TreeInsert(bst, 100))
    {
        ++err;
    }

    if (ERR_OK != TreeInsert(bst, 120))
    {
        ++err;
    }

    if (100 != GetDataRight(bst->m_root))
    {
        ++err;
    }

    if (5 != GetDataLeft(bst->m_root))
    {
        ++err;
    }

    current = GetNodeRight(bst->m_root);

    if (120 != GetDataRight(current))
    {
        ++err;
    }

    current = GetNodeLeft(bst->m_root);

    TreeDestroy(bst);

    PrintResualt(testName, scenario, err);
}

static void TestTreeInsertBigTree(void)
{
    Tree *bst = TreeCreate();
    int err = 0;
    char *testName = "TreeInsert";
    char *scenario = "BigTree";

    int arr[] = {50, 88, 99, 7, 4, 5, 6};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    size_t i = 0;

    for (; i < size; ++i)
    {
        TreeInsert(bst, arr[i]);
    }

    print2D(bst->m_root);

    PrintResualt(testName, scenario, err);
}

static void TestTreeInsertAfterDestroy(void)
{
    Tree *bst = TreeCreate();
    int err = 0;
    char *testName = "TreeInsert";
    char *scenario = "AfterDestroy";

    TreeDestroy(bst);

    if (ERR_NOT_INITIALZED != TreeInsert(bst, 11))
    {
        ++err;
    }

    PrintResualt(testName, scenario, err);
}

static void TestTreePrint(void)
{
    Tree *bst = TreeCreate();
    int err = 0;
    char *testName = "TreePrint";
    char *scenario = "";

    if (ERR_OK != TreeInsert(bst, 10))
    {
        ++err;
    }

    if (ERR_OK != TreeInsert(bst, 5))
    {
        ++err;
    }

    if (ERR_OK != TreeInsert(bst, 6))
    {
        ++err;
    }

    if (ERR_OK != TreeInsert(bst, 100))
    {
        ++err;
    }

    if (ERR_OK != TreeInsert(bst, 120))
    {
        ++err;
    }

    printf(BOLDRED "root: 10\n" RESET);

    printf(BOLDBLUE "POST_ORDER\n" RESET);
    TreePrint(bst, POST_ORDER);

    printf(BOLDRED "root: 10\n" RESET);
    printf(BOLDGREEN "IN_ORDER\n" RESET);
    TreePrint(bst, IN_ORDER);

    printf(BOLDRED "root: 10\n" RESET);
    printf(BOLDYELLOW "PRE_ORDER\n" RESET);
    TreePrint(bst, PRE_ORDER);

    printf("EMPTY_TREE\n");
    TreePrint(NULL, PRE_ORDER);

    TreeDestroy(bst);

    PrintResualt(testName, scenario, err);
}

static void TestTreeIsDataFoundDataNotExsist(void)
{
    Tree *bst = TreeCreate();
    int err = 0;
    char *testName = "IsDataFoundData";
    char *scenario = "NotExsist";

    TreeInsert(bst, 10);
    TreeInsert(bst, 5);

    if (0 != TreeIsDataFound(bst, 11))
    {
        ++err;
    }

    TreeDestroy(bst);

    PrintResualt(testName, scenario, err);
}

static void TestTreeIsDataFoundDataExsist(void)
{
    Tree *bst = TreeCreate();
    int err = 0;
    char *testName = "IsDataFoundData";
    char *scenario = "Exsist";

    TreeInsert(bst, 10);
    TreeInsert(bst, 5);

    if (1 != TreeIsDataFound(bst, 10))
    {
        ++err;
    }

    TreeDestroy(bst);

    PrintResualt(testName, scenario, err);
}

static void TestTreeIsTreeIsFullNULL(void)
{
    Tree *bst = TreeCreate();
    int err = 0;
    char *testName = "IsTreeIsFull";
    char *scenario = "NULL";

    if (FALSE != IsFullTree(NULL))
    {
        ++err;
    }

    TreeDestroy(bst);

    PrintResualt(testName, scenario, err);
}

static void TestTreeIsTreeIsFullFullTree(void)
{
    Tree *bst = TreeCreate();
    int err = 0;
    char *testName = "IsTreeIsFull";
    char *scenario = "FullTree";

    TreeInsert(bst, 100);
    TreeInsert(bst, 50);
    TreeInsert(bst, 150);

    if (TRUE != IsFullTree(bst))
    {
        ++err;
    }

    TreeDestroy(bst);

    PrintResualt(testName, scenario, err);
}

static void TestTreeIsTreeIsFullNotFullTree(void)
{
    Tree *bst = TreeCreate();
    int err = 0;
    char *testName = "IsTreeIsFull";
    char *scenario = "NotFullTree";

    TreeInsert(bst, 100);
    TreeInsert(bst, 50);
    TreeInsert(bst, 60);

    if (FALSE != IsFullTree(bst))
    {
        ++err;
    }

    TreeDestroy(bst);

    PrintResualt(testName, scenario, err);
}

static void TestAreSimilarTreeTree1NULL(void)
{
    Tree *bst1 = TreeCreate();
    int err = 0;
    char *testName = "AreSimilarTree";
    char *scenario = "Tree1NULL";

    if (FALSE != AreSimilarTree(bst1, NULL))
    {
        ++err;
    }

    TreeDestroy(bst1);

    PrintResualt(testName, scenario, err);
}

static void TestAreSimilarTreeTree2NULL(void)
{
    Tree *bst1 = TreeCreate();
    int err = 0;
    char *testName = "AreSimilarTree";
    char *scenario = "Tree2NULL";

    if (FALSE != AreSimilarTree(NULL, bst1))
    {
        ++err;
    }

    TreeDestroy(bst1);

    PrintResualt(testName, scenario, err);
}

static void TestAreSimilarTreeSimilar(void)
{
    Tree *bst1 = TreeCreate();
    Tree *bst2 = TreeCreate();
    int err = 0;
    char *testName = "AreSimilarTree";
    char *scenario = "TreeSimilar";

    TreeInsert(bst1, 60);
    TreeInsert(bst1, 100);
    TreeInsert(bst1, 50);

    TreeInsert(bst2, 1000);
    TreeInsert(bst2, 40);
    TreeInsert(bst2, 2000);

    if (TRUE != AreSimilarTree(bst1, bst2))
    {
        ++err;
    }

    TreeDestroy(bst1);
    TreeDestroy(bst2);

    PrintResualt(testName, scenario, err);
}

static void TestAreSimilarTreeNotSimilarLeft(void)
{
    Tree *bst1 = TreeCreate();
    Tree *bst2 = TreeCreate();
    int err = 0;
    char *testName = "AreSimilarTree";
    char *scenario = "TreeNotSimilarLeft";

    TreeInsert(bst1, 100);
    TreeInsert(bst1, 50);
    TreeInsert(bst1, 40);

    TreeInsert(bst2, 1000);
    TreeInsert(bst2, 40);
    TreeInsert(bst2, 2000);

    if (FALSE != AreSimilarTree(bst1, bst2))
    {
        ++err;
    }

    TreeDestroy(bst1);
    TreeDestroy(bst2);

    PrintResualt(testName, scenario, err);
}

static void TestAreSimilarTreeNotSimilarRight(void)
{
    Tree *bst1 = TreeCreate();
    Tree *bst2 = TreeCreate();
    int err = 0;
    char *testName = "AreSimilarTree";
    char *scenario = "TreeNotSimilarRight";

    TreeInsert(bst1, 100);
    TreeInsert(bst1, 200);
    TreeInsert(bst1, 400);

    TreeInsert(bst2, 1000);
    TreeInsert(bst2, 40);
    TreeInsert(bst2, 2000);

    if (FALSE != AreSimilarTree(bst1, bst2))
    {
        ++err;
    }

    TreeDestroy(bst1);
    TreeDestroy(bst2);

    PrintResualt(testName, scenario, err);
}


static void TestIsPerfectTreeNULL(void)
{
    Tree *bst = TreeCreate();
    int err = 0;
    char *testName = "IsPerfectTree";
    char *scenario = "NULL";

    if(FALSE != IsPerfectTree(NULL))
    {
        ++err;
    }

    PrintResualt(testName, scenario, err);
}

static void TestIsPerfectTreeNotPerfect(void)
{
    Tree *bst = TreeCreate();
    int err = 0;
    char *testName = "IsPerfectTree";
    char *scenario = "NotPerfect";

    TreeInsert(bst, 100);
    TreeInsert(bst, 50);
    TreeInsert(bst, 40);
    TreeInsert(bst, 30);
    TreeInsert(bst, 200);
    TreeInsert(bst, 90);
    TreeInsert(bst, 900);
    
    if(FALSE != IsPerfectTree(NULL))
    {
        ++err;
    }

    PrintResualt(testName, scenario, err);
}

static void TestIsPerfectTreePerfect(void)
{
    Tree *bst = TreeCreate();
    int err = 0;
    char *testName = "IsPerfectTree";
    char *scenario = "Perfect";

    TreeInsert(bst, 100);
    TreeInsert(bst, 50);
    TreeInsert(bst, 60);
    TreeInsert(bst, 40);
    TreeInsert(bst, 200);
    TreeInsert(bst, 300);
    TreeInsert(bst, 150);

    if(TRUE != IsPerfectTree(NULL))
    {
        ++err;
    }

    PrintResualt(testName, scenario, err);
}
/*------------- helpful functions -------------------------*/
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
