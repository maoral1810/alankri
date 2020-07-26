TARGET	= a.out
CC		= gcc
CFLAGS	= -ansi -g3 -pedantic -I../include -Wall -Werror
OBJS 	= heap.c heap_test.c

INC_DIR =../include/
LIB_DIR =../lib/
LIB_FLAG = -L -lDS

OBJS = heap.o heap_test.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
	
heap.o: heap.c $(INC_DIR)heap.h $(INC_DIR)vector.h vector.c
	$(CC) $(CFLAGS) -c heap.c $(LIB_FLAG)

heap_test.o: heap.c $(INC_DIR)heap.h $(INC_DIR)colors.h heap_test.c $(INC_DIR)vector.h vector.c
	$(CC) $(CFLAGS) -c heap_test.c $(LIB_FLAG)

valgrind: $(TARGET)
	valgrind ./$(TARGET)

clear:
	rm -f $(TARGET) $(OBJS) 
