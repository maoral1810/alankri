TARGET	= a.out
CC		= gcc
CFLAGS	= -ansi -g3 -pedantic -I../include #-Wall -Werror
OBJS 	= bst.c

INC_DIR =../include/

OBJS = bst.o bst_test.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
	
bst.o: bst.c $(INC_DIR)bst.h 
	$(CC) $(CFLAGS) -c bst.c

bst_test.o: bst.c $(INC_DIR)bst.h $(INC_DIR)colors.h bst_test.c 
	$(CC) $(CFLAGS) -c bst_test.c

valgrind: $(TARGET)
	valgrind ./$(TARGET)

clear:
	rm -f $(TARGET) $(OBJS) 


