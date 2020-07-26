TARGET	= a.out
CC		= g++
CFLAGS	= -ansi -g3 -pedantic 
OBJS 	= strings.o strings_test.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
	
strings.o: strings.cpp strings.h strings_test.cpp
	$(CC) $(CFLAGS) -c strings.cpp

strings_test.o: strings.cpp strings.h colors.h strings_test.cpp
	$(CC) $(CFLAGS) -c strings_test.cpp

valgrind: $(TARGET)
	valgrind ./$(TARGET)

clear:
	rm -f $(TARGET) $(OBJS) 


