TARGET	= a.out
CC		= g++
CFLAGS	= -ansi -pedantic -g3 -I../inc/
OBJS 	=   test_hash.o
INC_DIR =../inc/

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
	
test_hash.cpp.o: test_hash.cpp hash.h itr.h bucketContainer.h bucket.h hash_inl.h itr.h bucketContainer_inl.h bucket_inl.h
	$(CC) $(CFLAGS) -c test_hash.cpp

valgrind: $(TARGET)
	valgrind ./$(TARGET)
clear:
	rm -f $(TARGET) $(OBJS) 
