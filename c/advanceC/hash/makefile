TARGET	= a.out
CC		= gcc
CFLAGS	= -ansi -g3 -pedantic -I../include -Wall -Werror
OBJS 	= hash.c

INC_DIR =../include/
LIST_DIR = ../doublyLinkList/

OBJS = hash.o hash_test.o dllist.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) -lm

dllist.o: $(LIST_DIR)dllist.c $(INC_DIR)dllist.h $(INC_DIR)listfunctions.h $(INC_DIR)listitr.h
	$(CC) $(CFLAGS) -c $(LIST_DIR)dllist.c

hash.o: hash.c $(INC_DIR)hash.h $(INC_DIR)dllist.h $(INC_DIR)listfunctions.h $(INC_DIR)listitr.h $(LIST_DIR)dllist.c
	$(CC) $(CFLAGS) -c hash.c 

hash_test.o: hash.c $(INC_DIR)hash.h $(INC_DIR)colors.h hash_test.c $(INC_DIR)dllist.h $(INC_DIR)listfunctions.h $(INC_DIR)listitr.h $(LIST_DIR)dllist.c
	$(CC) $(CFLAGS) -c hash_test.c

valgrind: $(TARGET)
	valgrind ./$(TARGET)

clear:
	rm -f $(TARGET) $(OBJS) 


