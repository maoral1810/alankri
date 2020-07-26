CC	= g++ 
CXX = $(CC)

CFLAGS = -ansi -pedantic -Werror -Wall
CFLAGS += -g3
CXXFLAGS = $(CFLAGS) -std=c++03 

CPPFLAGS = -I$(INC_DIR)
LDFLAGS = 
LDLIBS =

INC_DIR = ../../include
SRC_DIR = ../../source

TARGET = test
OBJS = test.o

all: $(TARGET)

test.o: $(INC_DIR)/cyclic_fifo.hpp $(INC_DIR)/mu_test.h

check: $(TARGET)
	./$(TARGET) -v

test: $(OBJS)

clean:
	rm -f $(TARGET) $(OBJS) *.o

valgrind: $(TARGET)
	valgrind ./$(TARGET)

.PHONY: clean vlagrind check