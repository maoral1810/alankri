TARGET	= a.out
CPP		= g++ -pthread
CFLAGS	= -ansi -g3 -pedantic -I$(INC_DIR) -I$(SHAERD_PTR_DIR)
OBJS 	= mutex.o conditional_variable.o thread.o thread_pool.o thread_to_do.o test_thread_pool.o
INC_DIR = ../inc/
SHAERD_PTR_DIR = ../../reference_count/

$(TARGET): $(OBJS)
	$(CPP) -o $(TARGET) $(OBJS)

mutex.o: mutex.cpp $(INC_DIR)mutex.hpp $(INC_DIR)mutex_exception.hpp
	$(CPP) $(CFLAGS) -c mutex.cpp

conditional_variable.o: conditional_variable.cpp $(INC_DIR)conditional_variable.hpp $(INC_DIR)condition_var_exception.hpp $(INC_DIR)mutex.hpp
	$(CPP) $(CFLAGS) -c conditional_variable.cpp

thread.o: thread.cpp $(INC_DIR)thread.hpp $(INC_DIR)thread_exceptions.hpp
	$(CPP) $(CFLAGS) -c thread.cpp

thread_pool.o: thread_pool.cpp $(INC_DIR)thread_pool.hpp 
	$(CPP) $(CFLAGS) -c thread_pool.cpp

thread_to_do.o: thread_to_do.cpp $(INC_DIR)thread_to_do.hpp
	$(CPP) $(CFLAGS) -c thread_to_do.cpp

test_thread_pool.o: test_thread_pool.cpp $(INC_DIR)thread_pool.hpp 
	$(CPP) $(CFLAGS) -c test_thread_pool.cpp
	
valgrind: $(TARGET)
	valgrind ./$(TARGET)

clear:
	rm -f $(TARGET) $(OBJS) *.gch

