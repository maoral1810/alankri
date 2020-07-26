CC	= g++ -pthread 
CXX = g++

CFLAGS = -ansi -pedantic -Wall -Werror 
CFLAGS+= -g3
CXXFLAGS = $(CFLAGS) -std=c++03 
LDLFALSGS = -ldl
CPPFLAGS = -fpic 
SO_FLAGS = -shared

SRC_DIR = ../../source/
INC_DIR = ../../include/

OBJS =  main.o
SO_OBJS = cat.o

TARGET = main
SO_TARGET = libcat.so

$(SO_TARGET): $(SO_OBJS)
	$(CC) $(CPPFLAGS) $(SO_FLAGS) -o $(SO_TARGET) $(SO_OBJS) $(LDLFALSGS)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $(TARGET) $(OBJS) $(SO_OBJS) $(LDLFALSGS)

#dependency on header file.

all: $(SO_TARGET) $(SO_OBJS) $(TARGET) $(OBJS) 
	./$(TARGET) $(SO_TARGET)

check: $(SO_TARGET) $(SO_OBJS) $(TARGET) $(OBJS) 
	./$(TARGET) $(SO_TARGET)

so:	$(SO_TARGET) $(SO_OBJS)
	./$(SO_TARGET)

valgrind: $(TARGET)
	valgrind ./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS) $(SO_TARGET) $(SO_OBJS)

.PHONY: clean  vlagrind check