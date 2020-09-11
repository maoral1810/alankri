# makefile : Chat Project

CC = gcc
DS = ./ds
LIB_DIR = .
CFLAGS = -pedantic -g -I./$(DS)

SERVER_TARGET = chat_server.out
SERVER_OBJS = main.o server_manager.o users_manager.o group_manager.o server_network.o chat_protocol.o 

CLIENT_TARGET = chat_client.out
CLIENT_OBJS = client_app.o client_manager.o client_group_manager.o client_network.o client_ui.o chat_protocol.o

READ_TARGET = chat_read.out 
READ_OBJS = chat_read.o client_network.o client_ui.o chat_protocol.o

WRITE_TARGET = chat_write.out
WRITE_OBJS = chat_write.o client_network.o client_ui.o chat_protocol.o

all: $(CLIENT_TARGET) $(SERVER_TARGET) $(READ_TARGET) $(WRITE_TARGET)

$(SERVER_TARGET): $(SERVER_OBJS)
	$(CC) -o $(SERVER_TARGET) $(SERVER_OBJS) -L./$(LIB_DIR) -lChatDS
main.o: main.c
	$(CC) $(CFLAGS) -c main.c
server_manager.o: server_manager.c
	$(CC) $(CFLAGS) -c server_manager.c
users_manager.o: users_manager.c
	$(CC) $(CFLAGS) -c users_manager.c
group_manager.o: group_manager.c
	$(CC) $(CFLAGS) -c group_manager.c
server_network.o: server_network.c 
	$(CC) $(CFLAGS) -c server_network.c


$(CLIENT_TARGET) : $(CLIENT_OBJS)
	$(CC) -o $(CLIENT_TARGET) $(CLIENT_OBJS) -L./$(LIB_DIR) -lChatDS
client_app.o: client_app.c client_manager.h
	$(CC) $(CFLAGS) -c client_app.c
client_manager.o: client_manager.c client_manager.h client_group_manager.h client_network.h client_ui.h chat_protocol.h chat_protocol_limits.h
	$(CC) $(CFLAGS) -c client_manager.c
client_group_manager.o: client_group_manager.c client_group_manager.h
	$(CC) $(CFLAGS) -c client_group_manager.c
client_network.o: client_network.c client_network.h
	$(CC) $(CFLAGS) -c client_network.c
client_ui.o: client_ui.c client_ui.h chat_protocol_limits.h
	$(CC) $(CFLAGS) -c client_ui.c
	
chat_protocol.o: chat_protocol.c chat_protocol.h chat_protocol_limits.h
	$(CC) $(CFLAGS) -c chat_protocol.c
	
$(READ_TARGET) : $(READ_OBJS)
	$(CC) -o $(READ_TARGET) $(READ_OBJS)
chat_read.o: chat_read.c chat_protocol_limits.h client_network.h client_ui.h
	$(CC) $(CFLAGS) -c chat_read.c

$(WRITE_TARGET) : $(WRITE_OBJS)
	$(CC) -o $(WRITE_TARGET) $(WRITE_OBJS)
chat_write.o: chat_write.c chat_protocol_limits.h client_network.h client_ui.h
	$(CC) $(CFLAGS) -c chat_write.c

valgrind_server: $(SERVER_TARGET)
	valgrind ./$(SERVER_TARGET)
valgrind_client: $(CLIENT_TARGET)
	valgrind ./$(CLIENT_TARGET)
valgrind_read: $(READ_TARGET)
	valgrind ./$(READ_TARGET)
valgrind_write: $(WRITE_TARGET)
	valgrind ./$(WRITE_TARGET)

client:
	./chat_client.out

server:
	./chat_server.out

debug:
	gdb $(CLIENT_TARGET)

clean:
	rm -f *.out *.o *.gch *.txt