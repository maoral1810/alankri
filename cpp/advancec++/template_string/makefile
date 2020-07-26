TARGET	= a.out
CC		= g++
CFLAGS	= -ansi -pedantic -g3 
OBJS 	= template_string_test.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
	
template_string_test.o: template_string_test.cpp template_string.hpp template_string_inl.hpp
	$(CC) $(CFLAGS) -c template_string_test.cpp

valgrind: $(TARGET)
	valgrind ./$(TARGET)
clear:
	rm -f $(TARGET) $(OBJS) 