CC	= g++ 
CXX = $(CC)

CFLAGS = -ansi -pedantic -Werror -Wall -fPIC #-Wextra
CFLAGS += -g3 

CPPFLAGS = $(addprefix -I,$(INC_DIR) $(SO_DIR))
CPPFLAGS += -MMD -MP 

CXXFLAGS = $(CFLAGS) -std=c++03 

SO_FLAGS = -shared
LDFLAGS = -ldl
LDLIBS = -pthread 

SOURCES = $(TARGET).cpp
SOURCES += $(wildcard $(SRC_DIR)/*.cpp)
SOURCES += $(wildcard $(SO_DIR)/*.cpp)

SO_TARGET = libAgent.so

OBJS = $(SOURCES:.cpp=.o)
SO_OBJS = $(SO_SOURCES:.cpp=.o)

INC_DIR = ../../../inc
SRC_DIR = ../../../src
SO_DIR = ../../../so

TARGET = test

DEPENDS = $(OBJS:%.o=%.d) 

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDLIBS) -o $(TARGET) $(OBJS) $(LDFLAGS)

$(SO_TARGET): $(SO_OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(SO_FLAGS) $(LDLIBS) -o  $(SO_TARGET) $(SO_OBJS) $(OBJS) $(LDFLAGS)

all: $(SO_TARGET) $(SO_OBJS) $(TARGET) $(OBJS)
	./$(TARGET)

check: $(TARGET) $(OBJS) $(SO_TARGET) $(SO_OBJS)
	./$(TARGET) -v

valgrind:
	valgrind --leak-check=full ./$(TARGET)

clean: 
	rm -f $(OBJS) $(TARGET) $(DEPENDS) $(SO_TARGET) $(SO_OBJS) *.txt

debug:
	gdb ./test

-include $(DEPENDS)

.PHONY: clean check all valgrind