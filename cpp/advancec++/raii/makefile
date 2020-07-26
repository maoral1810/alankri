TARGET	= a.out
CPP		= g++ -pthread
CFLAGS	= -ansi -g3 -pedantic
OBJS 	=  single_ptr_test.o

$(TARGET): $(OBJS)
	$(CPP) -o $(TARGET) $(OBJS)

mutex.o: single_ptr_test.cpp single_ptr.hpp uncopyable.hpp
	$(CPP) $(CFLAGS) -c single_ptr_test.cpp

valgrind: $(TARGET)
	valgrind ./$(TARGET)

clear:
	rm -f $(TARGET) $(OBJS) *.gch

