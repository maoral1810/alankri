#include <stddef.h> 	/*size_t 			*/
#include <stdlib.h> 	/* malloc , free 	*/
#include <stdio.h> 		/* printf 			*/
#include "myMalloc.h" 	/* API myMalloc 	*/

#define MAGIC_NUMBER 0XACACACAC
#define MAGIC_DESTROY 0xBEDC0FFE

#define CHECK_BUFFER(_buffer)(( (_buffer != NULL ) && ((Mdata *)_buffer)->m_magicNumber) == MAGIC_NUMBER)
#define CHCEK_MYALLOC(_buffer)(_buffer == NULL || ((Mdata *)_buffer)->m_magicNumber != MAGIC_NUMBER  ||  ((Node *)((Mdata *)_buffer)->m_head) == NULL)

/* ----------- structs ----------- */
struct Mdata
{
	size_t m_magicNumber;
	size_t m_elementSize;
	size_t m_numOfElements;
	char *m_head;
};

typedef struct Node /* the Node struct is for readability of the code */
{
	void *m_next;
}Node;

/* -------------------- statics functions -----------------------*/
static void InitBuffer(void *_buffer);

/* -------------------- API Functions ---------------------------*/
void *CreateBuffer(size_t _numOfElements, size_t _sizeOfElement)
{
	void *buffer;
	size_t bufferSize;
	
	if(!_numOfElements || !_sizeOfElement)
	{
		return NULL;
	}

	if(_sizeOfElement < sizeof(void *))
	{
		_sizeOfElement = sizeof(void *);
	}
	
	bufferSize = _sizeOfElement * _numOfElements;
	
	buffer = malloc(bufferSize + sizeof(Mdata));
	
	if(buffer == NULL)
	{
		return NULL;
	}
	
	((Mdata *)buffer)->m_elementSize = _sizeOfElement;
	((Mdata *)buffer)->m_numOfElements = _numOfElements;
	((Mdata *)buffer)->m_head = (char *)buffer + sizeof(Mdata);
	((Mdata *)buffer)->m_magicNumber = MAGIC_NUMBER;
	InitBuffer(buffer);
	
	return buffer;
}

void DestroyBuffer(void *_buffer)
{
	if(CHECK_BUFFER(_buffer))
	{
		free(_buffer);
	}
}

void *MyMalloc(void *_buffer)
{
	Node *node = NULL;
	
	if(CHCEK_MYALLOC(_buffer))
	{
		return NULL;
	}

	node = (Node *)(((Mdata *)_buffer)->m_head);
	((Mdata *)_buffer)->m_head = node->m_next;
	
	return (void *)node;
}

void MyFree(void *_element, void *_buffer)
{
	if(_element != NULL && CHECK_BUFFER(_buffer))
	{
		((Node *)_element)->m_next = ((Mdata *)_buffer)->m_head;
		((Mdata *)_buffer)->m_head = _element;
	}
}

/* ----------------------------- static functions -----------------------------*/
static void InitBuffer(void *_buffer)
{
	char *runner = ((Mdata *)_buffer)->m_head;
	char *end = runner + (((Mdata *)_buffer)->m_elementSize * (((Mdata *)_buffer)->m_numOfElements - 1));

	while(runner != end)
	{
		((Node *)runner)->m_next = runner + ((Mdata *)_buffer)->m_elementSize; 
		runner += ((Mdata *)_buffer)->m_elementSize;
	}
		
	((Node *)runner)->m_next = NULL;
}

