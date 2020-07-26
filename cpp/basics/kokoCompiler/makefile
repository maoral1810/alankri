#	 makefile: 
TARGET = a.out
CC = g++
CFLAGS = -ansi -pedantic -g
OBJS = test.o parsar.o tokenaizer.o analyzer.o

$(TARGET) : $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

parsar.o: parsar.cpp  parsar.h tokenaizer.h
	$(CC) $(CFLAGS) -c parsar.cpp

tokenaizer.o: tokenaizer.cpp tokenaizer.h
	$(CC) $(CFLAGS) -c tokenaizer.cpp

analyzer.o: analyzer.h analyzer.cpp
	$(CC) $(CFLAGS) -c analyzer.cpp

test.o: parsar.h tokenaizer.h test.cpp
	$(CC) $(CFLAGS) -c test.cpp


valgrind: $(TARGET)
	valgrind ./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)
