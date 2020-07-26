TARGET	= a.out
CPP		= g++ -pthread
CFLAGS	= -ansi -g3 -O3 -pedantic
OBJS 	=  thread.o thread_test.o work_add.o #r_thread.o my_work.o

$(TARGET): $(OBJS)
	$(CPP) -o $(TARGET) $(OBJS)

thread.o: thread.hpp thread.cpp 
	$(CPP) $(CFLAGS) -c thread.cpp 

#r_thread.o: r_thread.cpp r_thread.hpp thread.hpp
#	$(CPP) $(CFLAGS) -c r_thread.cpp 
work_add.o: work_add.hpp  work_add.cpp
	$(CPP) $(CFLAGS) -c work_add.cpp 

thread_test.o: thread.hpp thread_test.cpp 
	$(CPP) $(CFLAGS) -c thread_test.cpp 

#my_work.o: my_work.hpp my_work.cpp runnable.hpp
#	$(CPP) $(CFLAGS) -c my_work.cpp 

valgrind: $(TARGET)
	valgrind ./$(TARGET)

clear:
	rm -f $(TARGET) $(OBJS) *.gch

