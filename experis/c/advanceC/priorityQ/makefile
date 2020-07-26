TARGET	= a.out
CC		= gcc
CFLAGS	= -ansi -g3 -pedantic -I../include -Wall -Werror
OBJS 	= vector.o heap.o priorityQ.o priorityQ_test.o 

INC_DIR =../include/
LIB_DIR =../lib/
LIB_FLAG = -L -lDS

HEAP_DIR = ../heap/
VECTOR_DIR = ../vector/

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

vector.o: $(INC_DIR)vector.h $(VECTOR_DIR)vector.c
	$(CC) $(CFLAGS) -c $(VECTOR_DIR)vector.c $(LIB_FLAG)

heap.o: $(HEAP_DIR)heap.c $(INC_DIR)heap.h $(INC_DIR)vector.h $(VECTOR_DIR)vector.c 
	$(CC) $(CFLAGS) -c $(HEAP_DIR)heap.c $(LIB_FLAG)

priorityQ.o: priorityQ.c $(HEAP_DIR)heap.c $(INC_DIR)heap.h $(INC_DIR)vector.h $(VECTOR_DIR)vector.c $(INC_DIR)priorityQ.h
	$(CC) $(CFLAGS) -c priorityQ.c $(LIB_FLAG)

priorityQ_test.o: priorityQ.c $(HEAP_DIR)heap.c $(INC_DIR)heap.h $(INC_DIR)vector.h $(VECTOR_DIR)vector.c $(INC_DIR)priorityQ.h
	$(CC) $(CFLAGS) -c priorityQ_test.c $(LIB_FLAG)

valgrind: $(TARGET)
	valgrind ./$(TARGET)

clear:
	rm -f $(TARGET) $(OBJS) 
