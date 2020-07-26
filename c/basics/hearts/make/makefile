#Hearts Project makefile
TARGET = Hearts.out
CC = gcc
CFLAGS =  -g -ansi -pedantic -Wall -Werror -I../include -I../../ds/include

SRC_DIR = ../src
INC_DIR = ../include

DS_INC_DIR = ../../../ds/include
DS_VECTOR_SRC_DIR = ../../../ds/src
DS_HEAP_SRC_DIR = ../../../ds/src

OBJS = player.o vector.o heap.o hand.o deck.o game.o trick.o round.o strategy.o table .o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

player.o :  $(SRC_DIR)/player.c $(INC_DIR)/player.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/player.c

#Strategy.o: $(SRC_DIR)/strategy.c $(INC_DIR)/strategy.h
#	$(CC) $(CFLAGS) -c $(SRC_DIR)/strategy.c

Deck.o: $(SRC_DIR)/deck.c $(INC_DIR)/deck.h $(INC_DIR)/card.h $(INC_DIR)/heartsErr.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/deck.c

vector.o: $(DS_VECTOR_SRC_DIR)/vector.c $(DS_INC_DIR)/vector.h $(DS_INC_DIR)/ADTDefs.h
	$(CC) $(CFLAGS) -c $(DS_VECTOR_SRC_DIR)/vector.c

heap.o: $(DS_HEAP_SRC_DIR)/heap.c $(DS_INC_DIR)/vector.h $(DS_INC_DIR)/ADTDefs.h  $(DS_INC_DIR)/heap.h
	$(CC) $(CFLAGS) -c $(DS_HEAP_SRC_DIR)/Heap.c

hand.o: $(SRC_DIR)/hand.c $(DS_INC_DIR)/vector.h $(DS_INC_DIR)/ADTDefs.h $(DS_INC_DIR)/heap.h $(INC_DIR)/card.h $(INC_DIR)/hand.h 
	$(CC) $(CFLAGS) -c $(SRC_DIR)/hand.c

clean:
	rm -f $(TARGET) $(OBJS)
