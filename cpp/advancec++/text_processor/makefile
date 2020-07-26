TARGET	= a.out
CPP		= g++
CFLAGS	= -ansi -g3 -pedantic 
OBJS 	=  io_filter_test.o #processor.o


$(TARGET): $(OBJS)
	$(CPP) -o $(TARGET) $(OBJS)

io_filter_test.o: string_input.hpp io_filter_test.cpp 
	$(CPP) $(CFLAGS) -c io_filter_test.cpp

#processor.o: processor.hpp processor.cpp 
#	$(CPP) $(CFLAGS) -c processor.cpp

valgrind: $(TARGET)
	valgrind ./$(TARGET)

clear:
	rm -f $(TARGET) $(OBJS) *.gch

