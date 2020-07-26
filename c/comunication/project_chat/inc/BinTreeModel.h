#ifndef __BIN_TREE_MODEL_H__
#define __BIN_TREE_MODEL_H__
#include "BinTree.h"

typedef struct Node Node;

struct Node
{
	void* m_data;
	Node* m_left;
	Node* m_right;
	Node* m_father;
};

struct BSTree
{
	size_t m_magicNumber;
	Node m_sentinel;
	LessComparator m_lessFunc;
};

#endif /*__BIN_TREE_MODEL_H__*/
