TARGET	= a.out
CC		= gcc
CFLAGS	= -ansi -g3 -pedantic -I../include -Wall -Werror
OBJS 	= dllist.c

INC_DIR =../include/

OBJS = dllist.o dllist_test.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
	
dllist.o: dllist.c $(INC_DIR)dllist.h $(INC_DIR)listfunctions.h
	$(CC) $(CFLAGS) -c dllist.c

dllist_test.o: dllist.c $(INC_DIR)dllist.h $(INC_DIR)colors.h dllist_test.c $(INC_DIR)listfunctions.h
	$(CC) $(CFLAGS) -c dllist_test.c

valgrind: $(TARGET)
	valgrind ./$(TARGET)

clear:
	rm -f $(TARGET) $(OBJS) 


