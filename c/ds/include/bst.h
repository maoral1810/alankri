#ifndef __BST_H__
#define __BST_H__

#include "ADTDefs.h"
#define TRUE 1
#define FALSE 0

typedef struct Tree Tree;
typedef struct Node Node;

struct  Tree
{
    Node *m_root;
    size_t magicNumber;
};

typedef enum
{
    PRE_ORDER,
    IN_ORDER,
    POST_ORDER
}TreeTraverse;

/*
    the function create a tree and return a pointer to tree
    intput:

    output:
        pointer to tree
    
    error:
        return NULL on failure 
*/
Tree *TreeCreate();
/*
    the function destroyed a tree (PostOrder)

    input:
        tree - pointer to tree
    
    error:
*/
void TreeDestroy(Tree *_tree); /* postOrder*/
/* 
    the function Insert a data to tree (InOrder)

    input:
        tree - pointer to tree
        data - data to insert

    output:
        return status - ERR_OK on sucsses

    error:
        ERR_DATA_EXSIST - if the data exsist
        ERR_NOT_INITIALIZED - if tree is NULL
*/
ADTErr TreeInsert(Tree *_tree, int _data);
/* 
    the function search if data is apear in tree

    input:
        tree - pointer to tree
        data - data to search
    
    output:
        0 - on failure
        !0 - on sucsses
    
    error:
        ERR_NOT_INITIALZED - if tree is NULL
*/
int TreeIsDataFound(Tree *_tree, int _data);
/* 
    the function print tree 

    input:
        tree - pointer to tree
        traverseMode - the traverse methood
    
    output:

    error:

*/
void TreePrint(Tree *_tree, TreeTraverse _traverseMode);
/*     
    the function return if tree is full tree or not
    full tree - all node have 2 or 0 children

    input:
        tree - pointer to tree
    
    output:
        0 - on failure
        !0 - on sucsses
    
    error:
        return false if tree is NULL 
*/
int IsFullTree(Tree *_tree);
/* 
    the function return if tree1 is similar to tree2 or not(in structure not data)

    input:
        tree1 - pointer to tree1
        tree2 - pointer to tree2
    
    output:
        0 - on failure
        !0 - on sucsses
    
    error:
        return false if tree1 or tree2 are NULL 
*/
int AreSimilarTree(Tree *_tree1, Tree *_tree2);
/* 
    the function return if tree is perfect tree or not
    perfect tree - every sub tree is full tree && sub right tree have same hight 
    of sub tree left
    example:

                5
              /   \
             3    10
            / \   / \
           1   4 9   20
           
    input:
        tree - pointer to tree
    
    output:
        0 - on failure
        !0 - on sucsses
    
    error:
        return false if tree is NULL 
*/
int IsPerfectTree(Tree *_tree);
#endif /* __BST_H__ */