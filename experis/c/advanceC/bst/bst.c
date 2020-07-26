#include <stdlib.h> /* malloc , free*/
#include <assert.h> /* assert       */
#include "bst.h"    /* BST API*/

#define MAGIC_NUMBER 0XACACACAC
#define MAGIC_DESTROY 0xBEDC0FFE
#define FALSE 0
#define TRUE !FALSE

typedef enum {left, right} branch;

struct BSTNode
{
    void *m_data;
    struct BSTNode *m_parent;
    struct BSTNode *m_children[2];
};

struct BSTree
{
    size_t m_magicNumber;
    BSTNode m_root;
    LessComparator m_sortingMethod;
};

struct BSTreeItr
{
    BSTNode *m_node;
};

static void InitBSTNode(BSTNode *new, BSTNode *parent, void *data);
static BSTNode *MoveInTree(BSTNode *_BSTNode, branch _direction);
static BSTreeItr FindPlaceToInsert(BSTree *_tree, void *_item);
/* destroy functions */
static void NodeDestroy(BSTNode* _node);
static void RecBSTreeDestroy(BSTNode *_root, void (*_destroyer)(void*));
/* foreach functions */
/* static BSTreeItr PostOrderForEach(BSTreeItr _begin, BSTreeItr _end, 
                                ActionFunction _act, void *_context);
static BSTreeItr InOrderForEach(BSTreeItr _begin, BSTreeItr _end, 
                                ActionFunction _act, void *_context);
static BSTreeItr PreOrderForEach(BSTreeItr _begin, BSTreeItr _end, 
                                ActionFunction _act, void *_context); */

static BSTNode g_wrongBSTNode = {NULL, &g_wrongBSTNode, {(&g_wrongBSTNode), (&g_wrongBSTNode)}};
BSTreeItr g_BSTWrongIter = {(BSTreeItr)&g_wrongBSTNode};

BSTree* BSTreeCreate(LessComparator _less)
{
    BSTree *newBst = NULL;
    if(_less == NULL)
    {
        return NULL;
    }
    
    newBst = (BSTree *)malloc(sizeof(BSTree));

    if (NULL == newBst)
    {
        return NULL;
    }

    newBst->m_sortingMethod = _less;
    newBst->m_root.m_children[left] = &(newBst->m_root);
    newBst->m_root.m_children[right] = &(newBst->m_root);
    newBst->m_root.m_parent = &(newBst->m_root);
    newBst->m_magicNumber = MAGIC_NUMBER;

    return newBst;
}

void BSTreeDestroy(BSTree* _tree, void (*_destroyer)(void*))
{
    if(_tree != NULL && _tree->m_magicNumber == MAGIC_NUMBER)
    {
        _tree->m_magicNumber = MAGIC_DESTROY;
        if(_destroyer != NULL)
        {
            RecBSTreeDestroy((_tree->m_root.m_children[left]), _destroyer);
        }

        free(_tree);
    }
}

BSTNode *BSTreeInsert(BSTree* _tree, void* _item)
{
    BSTNode *newNode = NULL;
    BSTreeItr placeToInsert;
    branch side = left;

    if(_tree == NULL || _item == NULL || _tree ->m_magicNumber != MAGIC_NUMBER)
    {
        return BSTreeItrEnd(_tree);
    }

    newNode = (BSTNode *)malloc(sizeof(BSTNode));
    if(newNode == NULL)
    {
        return BSTreeItrEnd(_tree);
    }

    if(BSTreeItrEquals(BSTreeItrBegin(_tree), BSTreeItrEnd(_tree))) /* empty tree */
    {
        InitBSTNode(newNode, &(_tree->m_root) ,_item);
        _tree->m_root.m_children[left] = newNode;
        placeToInsert->m_node = newNode;
/*         return(BSTreeItrBegin(_tree)); */
        return placeToInsert;
    }

    placeToInsert = FindPlaceToInsert(_tree, _item);
    
    if(BSTreeItrEquals(placeToInsert, BSTreeItrEnd(_tree))) /* duplicated*/
    {
        free(newNode);
        return placeToInsert;
    }

    InitBSTNode(newNode, placeToInsert->m_node , _item);

    if(_tree->m_sortingMethod(placeToInsert->m_node->m_data, _item))
    {
        side = right;
    }
    
    placeToInsert->m_node->m_children[side] = newNode;
/*     placeToInsert->m_node = placeToInsert->m_node->m_children[side]; */
    return (BSTreeItr)newNode;
}

BSTreeItr BSTreeFindFirst(const BSTree* _tree, PredicateFunction _predicate, void* _context)
{
    BSTreeItr runner;
    BSTreeItr end;

    if(_tree == NULL || _tree ->m_magicNumber != MAGIC_NUMBER || 
       _context == NULL || _predicate == NULL)
    {
        return BSTreeItrEnd(_tree);
    }

    runner = BSTreeItrBegin(_tree);
    end = BSTreeItrEnd(_tree);

    while(!BSTreeItrEquals(runner, end))
    {
        if(_predicate(runner->m_node->m_data, _context))
        {
            break;
        }

        runner = BSTreeItrNext(runner);
    }

    return runner;
}

BSTreeItr BSTreeItrBegin(const BSTree* _tree)
{
    BSTNode *current;

    if(_tree == NULL || _tree ->m_magicNumber != MAGIC_NUMBER)
    {
        return g_BSTWrongIter;
    }
    
    current = &((BSTree *)_tree)->m_root;

    while(current->m_children[left] != current)
    {
        current = current->m_children[left];
    }
    
    return (BSTreeItr)current;
}

BSTreeItr BSTreeItrEnd(const BSTree* _tree)
{
    if(_tree == NULL || _tree ->m_magicNumber != MAGIC_NUMBER)
    {
        return g_BSTWrongIter;
    }

    return (BSTreeItr)&(_tree->m_root);
}

int BSTreeItrEquals(BSTreeItr _a, BSTreeItr _b)
{
    if(_a != g_BSTWrongIter && _b != g_BSTWrongIter)
    {
        return _a == _b;
    }

    return FALSE;
}

BSTreeItr BSTreeItrNext(BSTreeItr _it)
{
    if(_it != g_BSTWrongIter)
    {
        return (BSTreeItr)MoveInTree(_it->m_node, right);
    }

    return g_BSTWrongIter;
}

BSTreeItr BSTreeItrPrev(BSTreeItr _it)
{
    if(_it != g_BSTWrongIter)
    {
        return (BSTreeItr)MoveInTree(_it->m_node, left);
    }

    return g_BSTWrongIter;
}

/* void* BSTreeItrRemove(BSTreeItr _it)
{
    BSTreeItr begin = _it;
    BSTreeItr end = _it;
    ListBSTNode *list;

    if(_it == g_BSTWrongIter)
    {
        return NULL;
    }

    while(!BSTreeItrEquals(begin , BSTreeItrPrev(begin)))
    {
        begin = BSTreeItrPrev(begin);
    }

    while (!BSTreeItrEquals(end , BSTreeItrNext(end)))
    {
        end = BSTreeItrNext(end);
    }
    
    list = Tree2List(begin, end);

    (Node *)_it

    

} */

void* BSTreeItrGet(BSTreeItr _it)
{
    if(_it != g_BSTWrongIter)
    {
        return (_it->m_node->m_data);
    }

    return NULL;
}

/* BSTreeItr BSTreeForEach(const BSTree* _tree, TreeTraversalMode _mode,
                 ActionFunction _action, void* _context)
{
    BSTreeItr begin;
    BSTreeItr end;
    BSTreeItr resItr;

    if(_tree == NULL || _action == NULL)
    {
        return g_BSTWrongIter;
    }

    begin = BSTreeItrBegin(_tree);
    end = BSTreeItrEnd(_tree);

    switch (_mode)
    {
        case BSTREE_TRAVERSAL_PREORDER:
            resItr = PreOrderForEach(begin, end, _action, _context);
            break;

        case BSTREE_TRAVERSAL_INORDER:
            resItr = InOrderForEach(begin, end, _action, _context);
            break;

        case BSTREE_TRAVERSAL_POSTORDER:
            resItr = PostOrderForEach(begin, end, _action, _context);
            break;
 */
/*         case BSTREE_TRAVERSAL_DEPTH_FIRST:
        break;

        case BSTREE_TRAVERSAL_BREADTH_FIRST:
        break; */
    
/*         default:
            break;
    }

    return resItr;
} */

/* ------------------------- static function ------------------------------*/
static void InitBSTNode(BSTNode *new, BSTNode *parent, void *data)
{
    new->m_data = data;
    new->m_parent = parent;
    new->m_children[right] = new;
    new->m_children[left] = new;
}

static void RecBSTreeDestroy(BSTNode *_root, void (*_destroyer)(void*))
{
    if(_root == _root->m_children[right] && _root == _root->m_children[left])
    {
        return;
    }

    RecBSTreeDestroy(_root->m_children[left] , _destroyer);
    RecBSTreeDestroy(_root->m_children[right], _destroyer);
    if(_destroyer != NULL)
    {
       _destroyer(_root); 
    }

    NodeDestroy(_root);
}

static void NodeDestroy(BSTNode* _node)
{
	assert(_node != NULL);
	free(_node);
}

static BSTNode *MoveInTree(BSTNode *_node, branch _direction)
{
    if(_node != _node->m_children[_direction])
    {
        _node = _node->m_children[_direction];
        
        while (_node != _node->m_children[!_direction])
        {
            _node = _node->m_children[!_direction];
        } 
    }
    else
    {
        while (_node == _node->m_parent->m_children[_direction])
        {
            _node = _node->m_parent;
        }

        _node = _node->m_parent;
    }
    
    return _node;
}

static BSTreeItr FindPlaceToInsert(BSTree *_tree, void *_item)
{
    BSTNode *nodeRunner = &(_tree->m_root);
    branch side  = left;
    BSTreeItr itr = BSTreeItrBegin(_tree);

    while (nodeRunner != nodeRunner->m_children[side])
    {
        nodeRunner = nodeRunner->m_children[side];

        if( _tree->m_sortingMethod(nodeRunner->m_data, _item))
        {
            side = right;
        }
        else if (_tree->m_sortingMethod(_item ,nodeRunner->m_data))
        {
            side = left;
        }
        else
        {
            return BSTreeItrEnd(_tree); 
        }       
    }

    itr->m_node= nodeRunner;
    return itr;
}

/* static BSTNode *FindPlaceToInsert(BSTree *_tree, void *_item) 
{
    BSTNode *father = &(_tree->m_root);
    BSTNode *currentNode = _tree->m_root.m_children[left];

    while(currentNode != father)
    {
        if(_tree->m_sortingMethod(_item, currentNode))
        {
            currentNode = currentNode->m_children[left];
        }
        else if(_tree->m_sortingMethod(currentNode, _item))
        {
            currentNode = currentNode->m_children[right];
        }
        else
        {
            return &g_wrongBSTNode;
        }
        
    }
} */

/* static BSTreeItr PostOrderForEach(BSTreeItr _begin, BSTreeItr _end, 
                        ActionFunction _act, void *_context)
{
    if(BSTreeItrEquals(_begin, _end))
    {
        return _begin;
    }

    _begin = PostOrderForEach((BSTreeItr)_begin->m_node->m_children[left], 
                            _end, _act, _context);
    _begin = PostOrderForEach((BSTreeItr)_begin->m_node->m_children[right], 
                            _end, _act, _context);

    if(!_act(BSTreeItrGet(_begin),_context))
    {
        _end = _begin;
    }
} */

/* static BSTreeItr InOrderForEach(BSTreeItr _begin, BSTreeItr _end, 
                      ActionFunction _act, void *_context)
{
    while(!BSTreeItrEquals(_begin, _end))
    {
        if(!_act(BSTreeItrGet(_begin),_context))
        {
            break;
        }

        _begin = BSTreeItrNext(_begin);
    }

    return _begin;
} */

/* static BSTreeItr PreOrderForEach(BSTreeItr _begin, BSTreeItr _end, 
                       ActionFunction _act, void *_context)
{
    if(BSTreeItrEquals(_begin, _end))
    {
        return _begin;
    }

    if(!_act(BSTreeItrGet(_begin),_context))
    {
        return _begin;
    }

    _begin = PostOrderForEach((BSTreeItr)_begin->m_node->m_children[left], 
                            _end, _act, _context);
    _begin = PostOrderForEach((BSTreeItr)_begin->m_node->m_children[right], 
                            _end, _act, _context);

} */




