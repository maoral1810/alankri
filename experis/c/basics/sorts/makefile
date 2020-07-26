# makefile sample

TARGET= sorts.out
CC= gcc
CFLAGS= -ansi -g -pedantic
OBJS= sorts.o vector.o sorts_test.o stack.o
TEXTFILES= sortsRes
VALFLAGS = valgrind 

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
	
sorts.o: sorts.c sorts.h vector.h ADTDefs.h stack.h stack.c
	$(CC) $(CFLAGS) -c sorts.c

vector.o: vector.c vector.h ADTDefs.h
	$(CC) $(CFLAGS) -c vector.c

stack.o: ADTDefs.h stack.h stack.c
	$(CC) $(CFLAGS) -c stack.c

sorts_test.o: sorts.c sorts.h vector.h sorts_test.c colors.h ADTDefs.h vector.c stack.h stack.c
	$(CC) $(CFLAGS) -c sorts_test.c

valgrind: $(TARGET)
	$(VALFLAGS) ./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS) $(TEXTFILES)
