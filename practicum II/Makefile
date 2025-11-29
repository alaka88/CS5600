# Makefile for RFS Practicum II
# Zhimin Wang
# 11/28/2025

CC = gcc
CFLAGS = -Wall -pthread

SERVER_SRC = server.c utils.c
CLIENT_SRC = client.c
SERVER_EXEC = server
CLIENT_EXEC = client
TEST_SCRIPT = test_rfs.sh

all: $(SERVER_EXEC) $(CLIENT_EXEC)

$(SERVER_EXEC): $(SERVER_SRC) rfs.h
	$(CC) $(SERVER_SRC) -o $(SERVER_EXEC) $(CFLAGS)

$(CLIENT_EXEC): $(CLIENT_SRC) rfs.h
	$(CC) $(CLIENT_SRC) -o $(CLIENT_EXEC) $(CFLAGS)

test: all
	chmod +x $(TEST_SCRIPT)
	./$(TEST_SCRIPT)

clean:
	rm -f $(SERVER_EXEC) $(CLIENT_EXEC) *.o *.txt
	rm -rf server_files
