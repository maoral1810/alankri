TARGET	= a.out
CPP		= g++
CFLAGS	= -ansi -g3 -pedantic 
OBJS 	= test_graph.o vertex.o graph.o
HASH_DIR = ../hash/

$(TARGET): $(OBJS)
	$(CPP) -o $(TARGET) $(OBJS)

vertex.o: vertex.cpp vertex.h
	$(CPP) $(CFLAGS) -c vertex.cpp

graph.o: graph.cpp graph.h vertex.h edge.h $(HASH_DIR)hash.h
	$(CPP) $(CFLAGS) -c graph.cpp

test_graph.o: test_graph.cpp MUTest.h $(HASH_DIR)bucket.h $(HASH_DIR)BucketItr.h $(HASH_DIR)bucketContainer.h $(HASH_DIR)bucketContainer_inl.h $(HASH_DIR)hash.h vertex.h edge.h graph.h
	$(CPP) $(CFLAGS) -c test_graph.cpp

valgrind: $(TARGET)
	valgrind ./$(TARGET)

clear:
	rm -f $(TARGET) $(OBJS) *.gch

