TARGET	= a.out
CPP		= g++ 
CFLAGS	= -ansi -g3 -pedantic 
OBJS 	= shared_ptr_test.o

all: $(TARGET) 

$(TARGET): $(OBJS) 
	$(CPP) -o $(TARGET) $(OBJS)

shared_ptr_test.o: shared_ptr_test.cpp reference_count.hpp shared_ptr.hpp
	$(CPP) $(CFLAGS) -c shared_ptr_test.cpp

valgrind:
	valgrind ./$(TARGET)

clear:
	rm -f $(TARGET) $(OBJS) *.gch