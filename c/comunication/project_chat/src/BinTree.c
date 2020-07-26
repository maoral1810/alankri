#include <stdlib.h> /*dynamic allocation, size_t*/
#include <assert.h>

#include "BinTreeModel.h"
#include "BinTree.h"

#define MAGIC_NUMBER 0xBEEFBEEF
#define MAGIC_NUMBER_AFTER_DESTROY 0xDEADBEEF

#define LEFT_INSERT -1
#define RIGHT_INSERT 1

#define TRUE  1
#define FALSE 0

#define TREE_CHECK(x) ((x) != NULL && (x)->m_magicNumber == MAGIC_NUMBER)

static Node g_wrongNode = {NULL, &g_wrongNode, &g_wrongNode, &g_wrongNode};
BSTreeItr g_wrongItrTree = (BSTreeItr)(&g_wrongNode);

/*-----------------------*/
static void SubTreeDestroyNoDestroyer(Node* _root);
static void SubTreeDestroyWithDestroyer(Node* _root, void (*_destroyer)(void*));
static Node* NodeCreate(BSTree* _tree, void* _item);
static void NodeDestroy(Node* _node);
static BSTreeItr BSTreeRootInsert(BSTree* _tree, Node* _nodeToInsert);
static Node* NodeFindWhereInsert(BSTree* _tree, Node* _node, void* _item, int* _flagWhereToInsert);
static BSTreeItr NodeInsert(Node* _nodeToInsert, Node* _nodeFather, int _flagWhereToInsert);
static Node* Find(const BSTree* _tree, Node* _root, PredicateFunction _predicate, void* _context);
static BSTreeItr ForEachInOrder(const BSTree* _tree, Node *_root, ActionFunction _action, void* _context);
static BSTreeItr ForEachPostOrder(const BSTree* _tree, Node *_root, ActionFunction _action, void* _context);
static BSTreeItr ForEachPreOrder(const BSTree* _tree, Node *_root, ActionFunction _action, void* _context);
/*-----------------------*/

BSTree* BSTreeCreate(LessComparator _less)
{
	BSTree* tree;
	
	if(_less == NULL)
	{
		return NULL;
	}

	tree = (BSTree*)malloc(sizeof(BSTree));
	
	if(tree != NULL)
	{
		tree->m_sentinel.m_right  = &(tree->m_sentinel);
		tree->m_sentinel.m_left   = &(tree->m_sentinel);
		tree->m_sentinel.m_father = &(tree->m_sentinel);
		tree->m_lessFunc = _less;
		tree->m_magicNumber = MAGIC_NUMBER;
	}

	return tree;
}

void  BSTreeDestroy(BSTree* _tree, void (*_destroyer)(void*))
{
	if(TREE_CHECK(_tree))
	{
		_tree->m_magicNumber = MAGIC_NUMBER_AFTER_DESTROY;

		if(_destroyer == NULL)
		{
			SubTreeDestroyNoDestroyer(_tree->m_sentinel.m_left);
		}
		else
		{
			SubTreeDestroyWithDestroyer(_tree->m_sentinel.m_left, _destroyer);
		}

		free(_tree);
	}
}

BSTreeItr BSTreeInsert(BSTree* _tree, void* _item)
{
	Node* nodeToInsert, *nodeBefore;
	int flagWhereToInsert; 

	if(!TREE_CHECK(_tree))
	{
		return BSTreeItrEnd(_tree);
	}

	nodeToInsert = NodeCreate(_tree, _item);
	
	if(nodeToInsert == NULL)
	{
		return BSTreeItrEnd(_tree);
	}

	if(_tree->m_sentinel.m_left == &(_tree->m_sentinel))
	{
		return BSTreeRootInsert(_tree, nodeToInsert);
	}	
	
	nodeBefore = NodeFindWhereInsert(_tree, _tree->m_sentinel.m_left, _item, &flagWhereToInsert);
	
	if(nodeBefore == &g_wrongNode)
	{
		NodeDestroy(nodeToInsert);
		return BSTreeItrEnd(_tree);
	}
	
	return NodeInsert(nodeToInsert, nodeBefore, flagWhereToInsert); 
}

BSTreeItr BSTreeItrEnd(const BSTree* _tree)
{
	BSTree* tree = (BSTree*)_tree;
	BSTreeItr itr;
	
	if(!TREE_CHECK(_tree))
	{
		itr = g_wrongItrTree;
	}
	else
	{
		itr = (BSTreeItr)(&(tree->m_sentinel));
	}

	return itr;
}

int BSTreeItrEquals(BSTreeItr _a, BSTreeItr _b)
{
	return ((Node*)_a == (Node*)_b) ? TRUE : FALSE;
}

BSTreeItr BSTreeItrNext(BSTreeItr _it)
{
	Node* itr = (Node*)_it;

	if(itr->m_right != itr->m_right->m_right)
	{
		return (BSTreeItr)itr->m_right;
	}
	else
	{
		while(itr->m_father->m_right == itr)
		{
			itr = itr->m_father;
		}
		return (BSTreeItr)itr->m_father;
	}
}

void* BSTreeItrGet(BSTreeItr _it)
{
	Node* itr = (Node*)_it;

	return itr->m_data;
}

BSTreeItr BSTreeFindFirst(const BSTree* _tree, PredicateFunction _predicate, void* _context)
{
    Node *node;
    if (_tree == NULL || _predicate == NULL || _tree -> m_magicNumber != MAGIC_NUMBER)
    {
        return BSTreeItrEnd(_tree);
    }
    node = Find(_tree, _tree -> m_sentinel.m_left, _predicate, _context);
    if (!node)
    {
        return BSTreeItrEnd(_tree); 
    }
    return (node) ? (BSTreeItr)node : BSTreeItrEnd(_tree);
}


BSTreeItr BSTreeForEach(const BSTree* _tree, TreeTraversalMode _mode, ActionFunction _action, void* _context)
{
	if(_tree == NULL || _tree->m_magicNumber != MAGIC_NUMBER || _action == NULL)
	{
		return BSTreeItrEnd(_tree);
	}

	switch (_mode)
	{
		case BSTREE_TRAVERSAL_PREORDER:
			return ForEachPreOrder(_tree, _tree -> m_sentinel.m_left, _action, _context);
		case BSTREE_TRAVERSAL_INORDER:
			return ForEachInOrder(_tree, _tree -> m_sentinel.m_left, _action, _context);
		case BSTREE_TRAVERSAL_POSTORDER:
			return ForEachPostOrder(_tree, _tree -> m_sentinel.m_left, _action, _context);
	}
	return BSTreeItrEnd(_tree);
}

/*-----------------------------*/
static void SubTreeDestroyWithDestroyer(Node* _root, void (*_destroyer)(void*))
{
	if(_root == _root->m_father)
	{
		return;
	}

    SubTreeDestroyWithDestroyer(_root->m_left, _destroyer);
    SubTreeDestroyWithDestroyer(_root->m_right, _destroyer);
	_destroyer(_root->m_data);
	NodeDestroy( _root);
}

static void SubTreeDestroyNoDestroyer(Node* _root)
{
	if(_root == _root->m_father)
	{
		return;
	}

   	SubTreeDestroyNoDestroyer(_root->m_left);
    SubTreeDestroyNoDestroyer(_root->m_right);
	NodeDestroy(_root);
}

static Node* NodeCreate(BSTree* _tree, void* _item)
{
	Node* newNode;
	
	if(_item == NULL)
	{
		return NULL;
	}	

	newNode = (Node*)malloc(sizeof(Node));

	if(newNode != NULL)
	{
		newNode->m_data = _item;
		newNode->m_right = &(_tree->m_sentinel);
		newNode->m_left  = &(_tree->m_sentinel);
	}

	return newNode;
}

static void NodeDestroy(Node* _node)
{
	assert(_node != NULL);
	free(_node);
}

static BSTreeItr BSTreeRootInsert(BSTree* _tree, Node* _nodeToInsert)
{
	assert(_tree != NULL &&  _nodeToInsert != NULL);

	_tree->m_sentinel.m_left = _nodeToInsert;
	_nodeToInsert->m_father = &(_tree->m_sentinel);
	
	return (BSTreeItr)_nodeToInsert;
}

static Node* NodeFindWhereInsert(BSTree* _tree, Node* _node, void* _item, int* _flagWhereToInsert)
{
	Node* fatherNode;

	while(_node != _node->m_father)
	{
		fatherNode = _node;

		if(_tree->m_lessFunc(_item, _node->m_data))
		{
			*_flagWhereToInsert = LEFT_INSERT;
			_node = _node->m_left;
		}
		else if(_tree->m_lessFunc(_node->m_data, _item))
		{
			*_flagWhereToInsert = RIGHT_INSERT;
			_node = _node->m_right;
		}
		else
		{
			return &g_wrongNode;
		}
	}

	return fatherNode;
}

static BSTreeItr NodeInsert(Node* _nodeToInsert, Node* _nodeFather, int _flagWhereToInsert)
{
	_nodeToInsert->m_father = _nodeFather;

	if(_flagWhereToInsert == LEFT_INSERT)
	{
		_nodeFather->m_left = _nodeToInsert;
	}
	else
	{
		_nodeFather->m_right = _nodeToInsert;
	}

	return (BSTreeItr)_nodeToInsert;
}

static Node* Find(const BSTree* _tree, Node* _root, PredicateFunction _predicate, void* _context)
{
    Node *node;
    if (_root == &(_tree->m_sentinel))
    {
        return NULL;
    }
    if (_predicate(_root -> m_data, _context) == 0)
    {
        return _root;
    }
    node = Find(_tree, _root -> m_left, _predicate, _context);
    if (node != &(_tree->m_sentinel))
    {
        return node;
    }
    node = Find(_tree, _root -> m_right, _predicate, _context);
    if (node != &(_tree->m_sentinel))
    {
        return node;
    }
    return NULL;
}

static BSTreeItr ForEachInOrder(const BSTree* _tree, Node *_root, ActionFunction _action, void* _context)
{
    BSTreeItr node = NULL;
    if (_root == &(_tree->m_sentinel))
    {
        return NULL;
    }
    node = ForEachInOrder(_tree, _root -> m_left, _action, _context);
    if ((Node*)node != &(_tree->m_sentinel))
    {
        return node;
    }
    if (_action(_root -> m_data, _context) == 0)
    {
        return (BSTreeItr) _root;
    }
    node = ForEachInOrder(_tree, _root -> m_right, _action, _context);
    if ((Node*)node != &(_tree->m_sentinel))
    {
        return node;
    }
    return (BSTreeItr) node;
}



static BSTreeItr ForEachPreOrder(const BSTree* _tree, Node *_root, ActionFunction _action, void* _context)
{
    BSTreeItr node = NULL;
    if (_root == &(_tree->m_sentinel))
    {
        return NULL;
    }
    if (_action(_root -> m_data, _context) == 0)
    {
        return (BSTreeItr) _root;
    }
    node = ForEachPreOrder(_tree, _root -> m_left, _action, _context);
    if ((Node*)node != &(_tree->m_sentinel))
    {
        return node;
    }
    node = ForEachPreOrder(_tree, _root -> m_right, _action, _context);
    if ((Node*)node != &(_tree->m_sentinel))
    {
        return node;
    }
    return (BSTreeItr) node;
}


static BSTreeItr ForEachPostOrder(const BSTree* _tree, Node *_root, ActionFunction _action, void* _context)
{
    BSTreeItr node = NULL;
    if (_root == &(_tree->m_sentinel))
    {
        return NULL;
    }
    node = ForEachPostOrder(_tree, _root -> m_left, _action, _context);
    if ((Node*)node != &(_tree->m_sentinel))
    {
        return node;
    }
    
    node = ForEachPostOrder(_tree, _root -> m_right, _action, _context);
    if ((Node*)node != &(_tree->m_sentinel))
    {
        return node;
    }
    if (_action(_root -> m_data, _context) == 0)
    {
        return (BSTreeItr) _root;
    }
    return (BSTreeItr) node;
}

