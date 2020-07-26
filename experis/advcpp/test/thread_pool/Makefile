CC	= g++ 
CXX = $(CC)

CFLAGS = -ansi -pedantic -Werror -Wall
CFLAGS += -g3
CXXFLAGS = $(CFLAGS) -std=c++03 

CPPFLAGS = -I$(INC_DIR) -I$(SRC_DIR)
LDFLAGS = 
LDLIBS = -pthread

INC_DIR = ../../include
SRC_DIR = ../../source

TARGET = test
OBJS = test.o $(SRC_DIR)/mutex.o $(SRC_DIR)/condition_variable.o $(SRC_DIR)/thread_pool.o
OBJS += $(SRC_DIR)/asyncronize_task.o $(SRC_DIR)/threads_work.o $(SRC_DIR)/thread.o $(SRC_DIR)/poision_apple.o 
OBJS += $(SRC_DIR)/thread_group.o $(SRC_DIR)/excecutor.o $(SRC_DIR)/thread_group.o

all: $(TARGET)

test.o: $(INC_DIR)/thread_pool.hpp $(INC_DIR)/mu_test.h 

check: $(TARGET)
	./$(TARGET) -v

test: $(OBJS)

debug: $(TARGET)
	gdb ./$(TARGET) 
clean:
	rm -f $(TARGET) $(OBJS) *.o

valgrind: $(TARGET)
	valgrind ./$(TARGET)

.PHONY: clean vlagrind check