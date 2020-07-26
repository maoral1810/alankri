CC = g++
CXX = g++

CFLAGS = -ansi -pedantic -Wall -Werror
CFLAGS+= -g3
CXXFLAGS = $(CFLAGS) -std=c++03 

CPPFLAGS = -I$(TEST_DIR)
LDFLAGS = 
LDLIBS = 


TEST_DIR = ../../inc/

TARGET=test

#dependency on header file.
test.o: reduce.hpp

# test: test.o

check: $(TARGET) 
	./$(TARGET)

valgrind: $(TARGET)
	valgrind ./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS) *.o 

.PHONY: clean  vlagrind check