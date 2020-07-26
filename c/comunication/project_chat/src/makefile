SERVER_TARGET	= ser.out
CLIENT_TARGET	= cli.out
CC	= gcc
CFLAGS	= -g -ansi -pedantic -I../inc/ 
SERVER_OBJS		=  serverNet.o serverManager.o userManager.o serTest.o groupManager.o #app.o 
CLIENT_OBJS 	=  clientNet.o clientManager.o clientGroupManager.o test.o UI.o chatMan.o
OBJS = protocol.o hashmap.o 
INC_DIR =../inc/
LIB_PATH = ../inc/

all: $(SERVER_TARGET) $(CLIENT_TARGET)

$(SERVER_TARGET): $(SERVER_OBJS) $(OBJS)
	$(CC) -o $(SERVER_TARGET) $(SERVER_OBJS) $(OBJS) -L../inc -lList

$(CLIENT_TARGET): $(CLIENT_OBJS) $(OBJS)
	$(CC) -o $(CLIENT_TARGET) $(CLIENT_OBJS) $(OBJS) -L../inc -lList

serTest.o: serTest.c
	$(CC) $(CFLAGS) -c serTest.c

#app.o: app.c 
#	$(CC) $(CFLAGS) -c app.c

test.o: test.c 
	$(CC) $(CFLAGS) -c test.c

clientNet.o: clientNet.c $(INC_DIR)clientNet.h
	$(CC) $(CFLAGS) -c clientNet.c

clientManager.o: clientManager.c $(INC_DIR)clientManager.h
	$(CC) $(CFLAGS) -c clientManager.c

clientGroupManager.o: clientGroupManager.c $(INC_DIR)clientGroupManager.h
	$(CC) $(CFLAGS) -c clientGroupManager.c

protocol.o: protocol.c $(INC_DIR)ChatProtocol.h $(INC_DIR)ChatProtocolLimits.h
	$(CC) $(CFLAGS) -c protocol.c

UI.o: UI.c $(INC_DIR)UI.h $(INC_DIR)colors.h $(INC_DIR)errors.h
		$(CC) $(CFLAGS) -c UI.c

userManager.o: userManager.c $(INC_DIR)userManager.h 
	$(CC) $(CFLAGS) -c userManager.c

groupManager.o: groupManager.c $(INC_DIR)groupManager.h
	$(CC) $(CFLAGS) -c groupManager.c

chatMan.o: chatMan.c chatRead.c chatWrite.c $(INC_DIR)clientManager.h
	$(CC) $(CFLAGS) -c chatMan.c

hashmap.o: hashmap.c $(INC_DIR)hashmap.h 
	$(CC) $(CFLAGS) -c hashmap.c $(LIB_PATH)libList.a
	
serverNet.o: serverNet.c $(INC_DIR)serverNet.h 
	$(CC) $(CFLAGS) -c serverNet.c

serverManager.o: serverManager.c $(INC_DIR)serverManager.h 
	$(CC) $(CFLAGS) -c serverManager.c

valgrind: $(TARGET)
	valgrind ./$(TARGET)
clear:
	rm -f $(TARGET) $(OBJS) *.o *.out


