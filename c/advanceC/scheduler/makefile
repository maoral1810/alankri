TARGET	= a.out
CC		= gcc
CFLAGS	= -pedantic -I../include -g
OBJS 	= vector.o heap.o priorityQ.o timer.o task.o scheduler.o scheduler_test.o ZLog.o

INC_DIR =../include/
LIB_DIR =../lib/
LIB_FLAG = -L -lDS

HEAP_DIR = ../heap/
VECTOR_DIR = ../vector/
PQ_DIR = ../priorityQ/

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

vector.o: $(INC_DIR)vector.h $(VECTOR_DIR)vector.c
	$(CC) $(CFLAGS) -c $(VECTOR_DIR)vector.c

heap.o: $(HEAP_DIR)heap.c $(INC_DIR)heap.h $(INC_DIR)vector.h $(VECTOR_DIR)vector.c 
	$(CC) $(CFLAGS) -c $(HEAP_DIR)heap.c 

ZLog.o: ZLog.c ZLog.h
	$(CC) $(CFLAGS) -c ZLog.c
 
priorityQ.o: $(PQ_DIR)priorityQ.c $(HEAP_DIR)heap.c $(INC_DIR)heap.h $(INC_DIR)vector.h $(VECTOR_DIR)vector.c $(INC_DIR)priorityQ.h
	$(CC) $(CFLAGS) -c $(PQ_DIR)priorityQ.c

timer.o: timer.c timer.h ZLog.c ZLog.h
	$(CC) $(CFLAGS) -c timer.c
 
task.o:	task.h timer.h scheduler.h task.c timer.c scheduler.c ZLog.c ZLog.h
	$(CC) $(CFLAGS) -c task.c

scheduler.o: task.h timer.h scheduler.h task.c timer.c scheduler.c $(PQ_DIR)priorityQ.c $(HEAP_DIR)heap.c $(INC_DIR)heap.h $(INC_DIR)vector.h $(VECTOR_DIR)vector.c $(INC_DIR)priorityQ.h ZLog.c ZLog.h
	$(CC) $(CFLAGS) -c scheduler.c

scheduler_test.o: task.h timer.h scheduler.h task.c timer.c scheduler.c $(PQ_DIR)priorityQ.c $(HEAP_DIR)heap.c $(INC_DIR)heap.h $(INC_DIR)vector.h $(VECTOR_DIR)vector.c $(INC_DIR)priorityQ.h scheduler_test.c $(INC_DIR)colors.h
	$(CC) $(CFLAGS) -c scheduler_test.c

valgrind: $(TARGET)
	valgrind ./$(TARGET)

clear:
	rm -f $(TARGET) $(OBJS) *.log
