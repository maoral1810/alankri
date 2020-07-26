TARGET	= a.out
CPP		= g++ -pthread
CFLAGS	= -ansi -g3 -pedantic
OBJS 	=  mutex.o semaphore.o cyclic_waitable_q_test.o read_work.o write_work.o thread.o condision_variable.o
MUTEX_DIR = ../mutex/
SEMAPHORE_DIR = ../semaphore/
THREAD_DIR = ../thread/
COND_VAR_DIR = ../condision_variable/

CFLAGS += -I$(MUTEX_DIR)
CFLAGS += -I$(SEMAPHORE_DIR)
CFLAGS += -I$(THREAD_DIR)
CFLAGS += -I$(COND_VAR_DIR)

$(TARGET): $(OBJS)
	$(CPP) -o $(TARGET) $(OBJS)

mutex.o: $(MUTEX_DIR)mutex.hpp $(MUTEX_DIR)mutex.cpp $(MUTEX_DIR)mutex_exceptions.hpp
	$(CPP) $(CFLAGS) -c $(MUTEX_DIR)mutex.cpp 

semaphore.o: $(SEMAPHORE_DIR)semaphore.hpp $(SEMAPHORE_DIR)semaphore.cpp $(SEMAPHORE_DIR)semaphore_exceptions.hpp
	$(CPP) $(CFLAGS) -c $(SEMAPHORE_DIR)semaphore.cpp

condision_variable.o: $(COND_VAR_DIR)condision_variable.hpp $(COND_VAR_DIR)condision_variable.cpp $(MUTEX_DIR)mutex_exceptions.hpp
	$(CPP) $(CFLAGS) -c $(COND_VAR_DIR)condision_variable.cpp

read_work.o: $(THREAD_DIR)runnable.hpp read_work.hpp read_work.cpp cyclic_waitable_q.hpp
	$(CPP) $(CFLAGS) -c read_work.cpp 

write_work.o: $(THREAD_DIR)runnable.hpp write_work.hpp write_work.cpp cyclic_waitable_q.hpp
	$(CPP) $(CFLAGS) -c write_work.cpp 

thread.o: $(THREAD_DIR)thread.cpp $(THREAD_DIR)thread.hpp
	$(CPP) $(CFLAGS) -c $(THREAD_DIR)thread.cpp

cyclic_waitable_q_test.o: cyclic_waitable_q_test.cpp cyclic_waitable_q.hpp $(THREAD_DIR)thread.hpp $(THREAD_DIR)runnable.hpp MUTest.hpp cyclic_waitable_q_exceptions.hpp
	$(CPP) $(CFLAGS) -c cyclic_waitable_q_test.cpp

valgrind: $(TARGET)
	valgrind ./$(TARGET)

clear:
	rm -f $(TARGET) $(OBJS) *.gch

