TARGET	= a.out
CPP		= g++
CFLAGS	= -ansi -g3 -pedantic 
OBJS 	= bitset_reference.o bitset_test.o

$(TARGET): $(OBJS)
	$(CPP) -o $(TARGET) $(OBJS)

bitset_reference.o: bitset_reference.cpp bitset_reference.hpp 
	$(CPP) $(CFLAGS) -c bitset_reference.cpp

bitset_test.o: bitset_test.cpp bitset.hpp MUTest.hpp 
	$(CPP) $(CFLAGS) -c bitset_test.cpp

valgrind: $(TARGET)
	valgrind ./$(TARGET)

clear:
	rm -f $(TARGET) $(OBJS) *.gch

