TARGET	= a.out
CPP		= g++
CC		= gcc
CFLAGS	= -ansi -g3 -pedantic 
OBJS 	= vector_t.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
	
vector_t.o: vector_t.cpp vector_t.h continer_t.h
	$(CPP) $(CFLAGS) -c vector_t.cpp

Dlist_t.o: Dlist_t.cpp Dlist_t.h continer_t.h
	$(CPP) $(CFLAGS) -c Dlist_t.cpp

valgrind: $(TARGET)
	valgrind ./$(TARGET)

clear:
	rm -f $(TARGET) $(OBJS) 


