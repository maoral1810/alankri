CC	= g++ 
CXX = $(CC)

CFLAGS = -ansi -pedantic -Werror -Wall
CFLAGS += -g3
CXXFLAGS = $(CFLAGS) -std=c++03 

CPPFLAGS = -I$(INC_DIR)
LDFLAGS = 
LDLIBS = -pthread

INC_DIR = ../../include
SRC_DIR = ../../source

TARGET = test
OBJS = $(SRC_DIR)/thread.o $(SRC_DIR)/mutex.o $(SRC_DIR)/condition_variable.o test.o

all: $(TARGET)

check: $(TARGET)
	./$(TARGET) -v

test: $(OBJS)

#dependency
$(SRC_DIR)/thread.o: $(INC_DIR)/thread.hpp

$(SRC_DIR)/mutex.o: $(INC_DIR)/mutex.hpp $(INC_DIR)/common_utils.hpp

$(SRC_DIR)/condition_variable.o: $(INC_DIR)/condition_variable.hpp\
$(INC_DIR)/condition_variable_exceptions.hpp

# test
test.o: test.cpp $(INC_DIR)/mu_test.h $(INC_DIR)/waitable_bounded_queue.hpp\
$(INC_DIR)/condition_variable.hpp $(INC_DIR)/mutex.hpp

clean:
	rm -f $(TARGET) $(OBJS)

valgrind: $(TARGET)
	valgrind ./$(TARGET)

.PHONY: clean vlagrind check