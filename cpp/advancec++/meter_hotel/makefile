TARGET	= a.out
CPP		= g++
CFLAGS	= -ansi -g3 -pedantic 
OBJS 	= test.o km.o meter.o squreMeter.o hotel.o

$(TARGET): $(OBJS)
	$(CPP) -o $(TARGET) $(OBJS)
	
meter.o: meter.cpp km.h meter.h squreMeter.h
	$(CPP) $(CFLAGS) -c meter.cpp

squreMeter.o: squreMeter.cpp squreMeter.h 
	$(CPP) $(CFLAGS) -c squreMeter.cpp

km.o: km.cpp km.h 
	$(CPP) $(CFLAGS) -c km.cpp

hotel.o: hotel.cpp hotel.h 
	$(CPP) $(CFLAGS) -c hotel.cpp	

test.o: test.cpp squreMeter.h meter.h km.h
	$(CPP) $(CFLAGS) -c test.cpp

valgrind: $(TARGET)
	valgrind ./$(TARGET)

clear:
	rm -f $(TARGET) $(OBJS) 

