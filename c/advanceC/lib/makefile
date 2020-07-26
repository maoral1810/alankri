TARGET	= a.out
CC		= gcc
CFLAGS	= -pedantic -fPIC -I../include -g
OBJS 	= vector.o heap.o priorityQ.o bst.o queue.o dllist.o hash.o

INC_DIR =../include/
LIB_DIR =../lib/
LIB_FLAG = -L -lDS

HEAP_DIR = ../heap/
VECTOR_DIR = ../vector/
PQ_DIR = ../priorityQ/
BST_DIR = ../bst/
QUEUE_DIR = ../queue/
DUBLY_LINK_LIST_DIR = ../doublyLinkList/
HASH_DIR = ../hash/

$(TARGET): $(OBJS)
	$(CC) -o -lm $(TARGET) $(OBJS)
	
vector.o: $(INC_DIR)vector.h $(VECTOR_DIR)vector.c
	$(CC) $(CFLAGS) -c $(VECTOR_DIR)vector.c

heap.o: $(HEAP_DIR)heap.c $(INC_DIR)heap.h $(INC_DIR)vector.h $(VECTOR_DIR)vector.c 
	$(CC) $(CFLAGS) -c $(HEAP_DIR)heap.c 
 
priorityQ.o: $(PQ_DIR)priorityQ.c $(HEAP_DIR)heap.c $(INC_DIR)heap.h $(INC_DIR)vector.h $(VECTOR_DIR)vector.c $(INC_DIR)priorityQ.h
	$(CC) $(CFLAGS) -c $(PQ_DIR)priorityQ.c

bst.o: $(INC_DIR)bst.h $(BST_DIR)bst.c
	$(CC) $(CFLAGS) -c $(BST_DIR)bst.c

queue.o: $(INC_DIR)queue.h $(QUEUE_DIR)queue.c
	$(CC) $(CFLAGS) -c $(QUEUE_DIR)queue.c
	
dllist.o: $(INC_DIR)dllist.h $(DUBLY_LINK_LIST_DIR)dllist.c
	$(CC) $(CFLAGS) -c $(DUBLY_LINK_LIST_DIR)dllist.c
	
hash.o:$(INC_DIR)hash.h $(HASH_DIR)hash.c $(DUBLY_LINK_LIST_DIR)dllist.c
	$(CC) $(CFLAGS) -lm -c $(HASH_DIR)hash.c 

clear:
	rm -f $(TARGET) $(OBJS) *.log
