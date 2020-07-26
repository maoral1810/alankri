TARGET	= a.out
CC		= gcc
CFLAGS	= -ansi -g3 -pedantic -I../include -Wall -Werror
OBJS 	= vector.c

INC_DIR =../include/

OBJS = vector.o vector_test.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
	
vector.o: vector.c $(INC_DIR)vector.h
	$(CC) $(CFLAGS) -c vector.c

vector_test.o: vector.c $(INC_DIR)vector.h $(INC_DIR)colors.h vector_test.c
	$(CC) $(CFLAGS) -c vector_test.c

valgrind: $(TARGET)
	valgrind ./$(TARGET)

clear:
	rm -f $(TARGET) $(OBJS) 


