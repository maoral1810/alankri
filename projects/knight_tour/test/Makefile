CC	= gcc
CXX = $(CC)

CFLAGS = -ansi -pedantic -Werror -Wall -Wextra
CFLAGS += -g3 

CPPFLAGS = $(addprefix -I,$(INC_DIR))
CPPFLAGS += -MMD -MP 

CXXFLAGS = $(CFLAGS) -std=c++03 

SOURCES = $(TARGET).c
SOURCES += $(wildcard $(SRC_DIR)/*.c)

OBJS = $(SOURCES:.c=.o)

INC_DIR = ../inc
SRC_DIR = ../src

TARGET = knight_tour_test

DEPENDS = $(OBJS:%.o=%.d) 

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $(TARGET) $(OBJS)

all: $(TARGET) $(OBJS)
	./$(TARGET)

check: $(TARGET) $(OBJS)
	./$(TARGET) -v

valgrind:
	valgrind --leak-check=full ./$(TARGET)

clean: 
	rm -f $(OBJS) $(TARGET) $(DEPENDS)

debug:
	gdb ./knight_tour_test

-include $(DEPENDS)

.PHONY: clean check all valgrind