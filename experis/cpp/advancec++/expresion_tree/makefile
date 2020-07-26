TARGET	= a.out
CPP		= g++
CFLAGS	= -ansi -g3 -pedantic 
OBJS 	= expression_tree_test.o  operator_node.o number_node.o unary_operator_node.o parcer.o
HASH_DIR = ../hash/

$(TARGET): $(OBJS)
	$(CPP) -o $(TARGET) $(OBJS)

parcer.o: parcer.h parcer.cpp expression_node.h
	$(CPP) $(CFLAGS) -c parcer.cpp

unary_operator_node.o: unary_operator_node.h unary_operator_node.cpp
	$(CPP) $(CFLAGS) -c unary_operator_node.cpp
	
number_node.o: number_node.cpp number_node.h
	$(CPP) $(CFLAGS) -c number_node.cpp

operator_node.o: operator_node.cpp operator_node.h
	$(CPP) $(CFLAGS) -c operator_node.cpp

expression_tree_test.o: expression_tree_test.cpp number_node.h operator_node.h expression_node.h unary_operator_node.h
	$(CPP) $(CFLAGS) -c expression_tree_test.cpp

valgrind: $(TARGET)
	valgrind ./$(TARGET)

clear:
	rm -f $(TARGET) $(OBJS) *.gch

