# Makefile for Message Store Project
# Author: Zhimin Wang
# CS5600, Fall 2025

CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
OBJS = message.o store.o cache.o test_msg_store.o
TARGET = test_msg_store

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

message.o: message.c message.h
	$(CC) $(CFLAGS) -c message.c

store.o: store.c message.h
	$(CC) $(CFLAGS) -c store.c

cache.o: cache.c message.h
	$(CC) $(CFLAGS) -c cache.c

test_msg_store.o: test_msg_store.c message.h
	$(CC) $(CFLAGS) -c test_msg_store.c

clean:
	rm -f $(OBJS) $(TARGET) message_store.bin

run: $(TARGET)
	./$(TARGET)
