#	 makefile: Memory Manager

TARGET = a.out
CC = g++
CFLAGS = -ansi -pedantic -g
OBJS = manager.o page.o pool.o mem_test.o

$(TARGET) : $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

manager.o: manager.cpp manager.h
	$(CC) $(CFLAGS) -c manager.cpp

pool.o: pool.cpp pool.h manager.h page.h manager.cpp
	$(CC) $(CFLAGS) -c pool.cpp

page.o: page.cpp page.h manager.h manager.cpp
	$(CC) $(CFLAGS) -c page.cpp

mem_test.o: mem_test.cpp page.cpp page.h manager.h manager.cpp pool.cpp pool.h
	$(CC) $(CFLAGS) -c mem_test.cpp

valgrind: $(TARGET)
	valgrind ./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)
