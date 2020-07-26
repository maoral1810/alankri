TARGET	= a.out
CC		= g++
CFLAGS	= -ansi -g3 -pedantic 
OBJS 	= car.o bus.o private.o test.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
	
car.o: car.cpp car.h test.cpp
	$(CC) $(CFLAGS) -c car.cpp

bus.o: bus.cpp bus.h test.cpp car.h
	$(CC) $(CFLAGS) -c bus.cpp

private.o: private.cpp private.h test.cpp car.h
	$(CC) $(CFLAGS) -c private.cpp

test.o: private.cpp private.h car.cpp car.h bus.cpp bus.h test.cpp
	$(CC) $(CFLAGS) -c test.cpp

valgrind: $(TARGET)
	valgrind ./$(TARGET)

clear:
	rm -f $(TARGET) $(OBJS) 


