TARGET	= a.out
CC		= gcc
CFLAGS	= -ansi -g3 -pedantic -I../include -Wall -Werror
OBJS 	= queue.c

INC_DIR =../include/

OBJS = queue.o queue_test.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
	
queue.o: queue.c $(INC_DIR)queue.h
	$(CC) $(CFLAGS) -c queue.c

queue_test.o: queue.c $(INC_DIR)queue.h $(INC_DIR)colors.h queue_test.c
	$(CC) $(CFLAGS) -c queue_test.c

valgrind: $(TARGET)
	valgrind ./$(TARGET)

clear:
	rm -f $(TARGET) $(OBJS) 


