CC	= g++ 
CXX = $(CC)

CFLAGS = -ansi -pedantic -Werror -Wall -Wextra #-fPic
CFLAGS += -g3 

CPPFLAGS = $(addprefix -I,$(INC_DIR))
CPPFLAGS += -MMD -MP

CXXFLAGS = $(CFLAGS) -std=c++03 

LDFLAGS = #-ldl
LDLIBS = -pthread 

SOURCES = $(TARGET).cpp
SOURCES += $(wildcard ../../../src/*.cpp)

OBJS = $(SOURCES:.cpp=.o)

TARGET = test

INC_DIR = ../../../inc
SRC_DIR = ../../../src

DEPENDS = $(OBJS:%.o=%.d)

$(TARGET): $(OBJS)

all: $(TARGET)

check: $(TARGET)
	./$(TARGET) -v

valgrind:
	valgrind --leak-check=full ./$(TARGET)

clean: 
	rm -f $(OBJS) $(TARGET) $(DEPENDS)

debug:
	gdb ./test

-include $(DEPENDS)

.PHONY: clean check all valgrind