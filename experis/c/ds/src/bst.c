#include <stdio.h>  /* NULL        */
#include <stdlib.h> /* malloc ,free*/
#include "bst.h"
#include "bsthelpFucntions.h" /* gets functions */
#include "colors.h"

#define COUNT 2
#define MAGIC_NUMBER 0x88899765


struct  Node
{
    int m_data;
    Node *m_left;
    Node *m_right;
    Node *m_father;
};

static Node *CreateNode(int _data, Node *perant);
static void RecDestroyNode(Node *_node);
static void RecTreePrint(Node *_root, TreeTraverse _traverseMode);
static int RecIsDataFound(Node *_node, int _data);
static int IsEmptyTree(Tree *_tree);
static Node *TreeBubbleDown(Node *_node, int _data);
static InsertNode(Node *current, Node *nodeToInsert, int _data);
static int RecFullTree(Node *_node);
static int RecAreSimilarTree(Node *_node1, Node *_node2);
static int RecIsPerfectTree(Node *_node);

static void Recprint2D(Node *_root, int _space);

Tree *TreeCreate()
{
    Tree *bst = (Tree *)malloc(sizeof(Tree));

    if(NULL == bst)
    {
        return NULL;
    }

    bst->m_root = NULL;
    bst->magicNumber = MAGIC_NUMBER;

    return bst;
}

void TreeDestroy(Tree *_tree) /* postOrder*/
{
    if(NULL == _tree || MAGIC_NUMBER != _tree->magicNumber)
    {
        return;
    }
    
    RecDestroyNode(_tree->m_root);
    
    _tree->magicNumber = 0; 
    free(_tree);
}

ADTErr TreeInsert(Tree *_tree, int _data) /* inorder*/
{
    Node *current = NULL;
    Node *nodeToInsert = NULL;

    if(NULL == _tree || MAGIC_NUMBER != _tree->magicNumber)
    {
        return ERR_NOT_INITIALZED;
    }

    if(IsEmptyTree(_tree))
    {
        _tree->m_root = CreateNode(_data, NULL);
        if(_tree->m_root == NULL)
        {
            return ERR_ALLOCTAION_FAILED;
        }
        
        return ERR_OK;
    }
    
    current = TreeBubbleDown(_tree->m_root, _data);
    nodeToInsert = CreateNode(_data, current);
    if(nodeToInsert == NULL)
    {
        return ERR_ALLOCTAION_FAILED;
    }

    return InsertNode(current, nodeToInsert, _data);
}

int TreeIsDataFound(Tree *_tree, int _data)
{
    if(NULL == _tree)
    {
        return 0;
    }

    return RecIsDataFound(_tree->m_root, _data);
}

void TreePrint(Tree *_tree, TreeTraverse _traverseMode)
{
    if(NULL == _tree)
    {
        return;
    }

    RecTreePrint(_tree->m_root, _traverseMode);
}

int IsFullTree(Tree *_tree)
{
    if(NULL == _tree)
    {
        return FALSE;
    }

    return RecFullTree(_tree->m_root);
}

int AreSimilarTree(Tree *_tree1, Tree *_tree2)
{
    if(_tree1 == NULL || _tree2 == NULL)
    {
        return FALSE;
    }

    return RecAreSimilarTree(_tree1->m_root, _tree2->m_root);
}

int IsPerfectTree(Tree *_tree)
{
    if(_tree == NULL)
    {
        return FALSE;
    }

    return RecIsPerfectTree(_tree->m_root);
}

/* ----------------------- static functions ---------------------------- */
static Node *CreateNode(int _data, Node *perant)
{
    Node *node = NULL;

    node = (Node *)malloc(sizeof(Node));

    if(NULL == node)
    {
        return NULL;
    }

    node->m_data = _data;
    node->m_father = perant;
    node->m_left = NULL;
    node->m_right = NULL;

    return node;
}

static void RecDestroyNode(Node *_node)
{
    if(_node == NULL)
    {
        return;
    }

    RecDestroyNode(_node->m_left);
    RecDestroyNode(_node->m_right);

    free(_node);
}

static int RecIsDataFound(Node *_node, int _data)
{
    Node *currentNode = TreeBubbleDown(_node, _data);

    return (currentNode->m_data == _data);
}

static void RecTreePrint(Node *_root, TreeTraverse _traverseMode)
{
    if(_root == NULL)
    {
        return;
    }

    if(_traverseMode == IN_ORDER) /* Left, Root, Right */
    {
        RecTreePrint(_root->m_left, IN_ORDER);
        printf("%d\n", _root->m_data);
        RecTreePrint(_root->m_right, IN_ORDER);
    }

    else if(_traverseMode == POST_ORDER) /* Left, Right, Root */
    {
        RecTreePrint(_root->m_left, POST_ORDER);
        RecTreePrint(_root->m_right, POST_ORDER);
        printf("%d\n", _root->m_data);
    }

    else /* PREORDER (Root, Left, Right)*/
    {
        printf("%d\n", _root->m_data);
        RecTreePrint(_root->m_left, POST_ORDER);
        RecTreePrint(_root->m_right, POST_ORDER);
    }
}

static int IsEmptyTree(Tree *_tree)
{
    return (_tree ->m_root == NULL);
}

static void Recprint2D(Node *_root, int _space)
{
    int i = 0;
    /*  Base case  */
    if (_root == NULL) 
    {
        return; 
    }
    /*  Increase distance between levels  */
    _space += COUNT; 
  
    /* right child */
    Recprint2D(_root->m_right, _space); 
  
    /* Print current node after space */

    printf("\n"); 
    for (i = COUNT; i < _space; i++) 
    {
        printf(" "); 
    }    
    
    printf("%d\n", _root->m_data); 
  
    /*left child */ 
    Recprint2D(_root->m_left, _space); 
} 

void print2D(Node *_root) 
{ 
    /* Pass initial space count 0  */
   Recprint2D(_root, 0); 
} 

static Node *TreeBubbleDown(Node *_node, int _data)
{
    if(_node->m_data > _data && _node->m_left != NULL)
    {
        _node = TreeBubbleDown(_node->m_left, _data);
    }
    else if(_node->m_data < _data && _node->m_right != NULL)
    {
        _node = TreeBubbleDown(_node->m_right, _data);
    }

    return _node;
}

static InsertNode(Node *current, Node *nodeToInsert, int _data)
{
    ADTErr status = ERR_OK;
    
    if(current->m_data == _data)
    {
        return ERR_DATA_EXSIST;
    }

    nodeToInsert->m_data = _data;
    nodeToInsert->m_father = current;

    if(_data > current->m_data)
    {
        current->m_right = nodeToInsert;
    }
    else 
    {
        current->m_left = nodeToInsert;
    }

    return status;
}


static int RecFullTree(Node *_node)
{
    if(_node ->m_left == NULL && _node->m_right == NULL)/* i am leaf*/
    {
        return TRUE;
    }

    else if(_node ->m_left == NULL || _node->m_right == NULL) 
    {
        return FALSE;
    }
    

    return (RecFullTree(_node->m_left) &&  RecFullTree(_node->m_right));
}

static int RecAreSimilarTree(Node *_node1, Node *_node2)
{
    if((_node1 ->m_left == NULL && _node1->m_right == NULL) &&
        _node2 ->m_left == NULL && _node2->m_right == NULL)
    {
        return TRUE;
    }

    else if((_node1 ->m_left == NULL || _node2 ->m_left == NULL) ||
            (_node1 ->m_right == NULL || _node2 ->m_right == NULL))
    {
        return FALSE;
    }

    return (RecAreSimilarTree(_node1->m_left, _node2->m_left) &&  
            RecAreSimilarTree(_node1->m_right, _node1->m_right));
}

static int RecIsPerfectTree(Node *_node)
{
    static int rCounter = 0;
    static int lCounter = 0;

    if(_node ->m_left == NULL && _node->m_right == NULL)/* i am leaf*/
    {
        return TRUE;
    }

    else if(_node ->m_left == NULL || _node->m_right == NULL) 
    {
        return FALSE;
    }

    rCounter += RecIsPerfectTree(_node ->m_right);
    lCounter += RecIsPerfectTree(_node ->m_left); 

    printf("l counter = %d\n",lCounter);
    return (rCounter == lCounter);
}

/*--------------------- help functions -----------------*/

int GetDataRight(Node *_node)
{
    return _node->m_right->m_data;
}

int GetDataLeft(Node *_node)
{
    return _node->m_left->m_data;
}

Node *GetNodeRight(Node *_node)
{
    return _node->m_right;
}

Node *GetNodeLeft(Node *_node)
{
    return _node->m_right;
}



