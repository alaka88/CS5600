# ZW / sep 23/2025
# CS5600 - Assignmnet 3 - Implement Process Queue
# Makefile for process queue assignment
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g

OBJS = queue.o queuetest.o
TARGET = qtest

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

queue.o: queue.c queue.h
	$(CC) $(CFLAGS) -c queue.c

queuetest.o: queuetest.c queue.h
	$(CC) $(CFLAGS) -c queuetest.c

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
