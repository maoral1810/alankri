TARGET	= a.out
CPP		= g++ -pthread
CFLAGS	= -ansi -g3 -pedantic
OBJS 	=  mutex.o mutex_test.o

$(TARGET): $(OBJS)
	$(CPP) -o $(TARGET) $(OBJS)

mutex.o: mutex.hpp mutex.cpp 
	$(CPP) $(CFLAGS) -c mutex.cpp 

mutex_test.o: mutex_test.cpp mutex.hpp
	$(CPP) $(CFLAGS) -c mutex_test.cpp

valgrind: $(TARGET)
	valgrind ./$(TARGET)

clear:
	rm -f $(TARGET) $(OBJS) *.gch

