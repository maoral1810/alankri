#	 makefile: Memory Manager
TARGET = a.out
CC = g++
CFLAGS = -ansi -pedantic -g
OBJS = tCountiner_test.o

$(TARGET) : $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

container_test.o:  tCountiner_test.cpp  tContainer_t.h
	$(CC) $(CFLAGS) -c tCountiner_test.cpp

valgrind: $(TARGET)
	valgrind ./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)
