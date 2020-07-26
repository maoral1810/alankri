TARGET	= a.out
CC		= g++
CFLAGS	= -ansi -g3 -pedantic 
OBJS 	= IOtest.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
	
IOtest.o: IOtest.cpp virtIO_t.h binIO_t.h assciIO_t.h
	$(CC) $(CFLAGS) -c IOtest.cpp

valgrind: $(TARGET)
	valgrind ./$(TARGET)

clear:
	rm -f $(TARGET) $(OBJS) 


