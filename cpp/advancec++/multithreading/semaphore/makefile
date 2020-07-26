TARGET	= a.out
CPP		= g++ -pthread
CFLAGS	= -ansi -g3 -pedantic
OBJS 	=  semaphore.o semaphore_test.o

$(TARGET): $(OBJS)
	$(CPP) -o $(TARGET) $(OBJS)

semaphore.o: semaphore.hpp semaphore.cpp semaphore_exceptions.hpp
	$(CPP) $(CFLAGS) -c semaphore.cpp 

semaphore_test.o: semaphore_test.cpp semaphore.hpp
	$(CPP) $(CFLAGS) -c semaphore_test.cpp

valgrind: $(TARGET)
	valgrind ./$(TARGET)

clear:
	rm -f $(TARGET) $(OBJS) *.gch

