TARGET	= a.out
CC		= g++
CFLAGS	= -ansi -pedantic -g3 -I../include/
OBJS 	=   test.o


$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
	
test.o: test.cpp city.h street.h building.h
	$(CC) $(CFLAGS) -c test.cpp

valgrind: $(TARGET)
	valgrind ./$(TARGET)
clear:
	rm -f $(TARGET) $(OBJS) 

