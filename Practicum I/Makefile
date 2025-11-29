# Makefile for Memory Hierarchy Simulation - Part II
# Author: Zhimin Wang
# CS5600, Fall 2025

CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
OBJS = message.o store.o cache.o test_msg_store.o
TARGET = test_msg_store

# Optional configuration macros with defaults
CACHE_SIZE ?= 16
NUM_MESSAGES ?= 50
NUM_ACCESSES ?= 1000

# Macro flags for compilation
MACROS = -DCACHE_SIZE=$(CACHE_SIZE) -DNUM_MESSAGES=$(NUM_MESSAGES) -DNUM_ACCESSES=$(NUM_ACCESSES)

all: $(TARGET)

# Link all object files
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile individual source files with macros
message.o: message.c message.h
	$(CC) $(CFLAGS) $(MACROS) -c message.c

store.o: store.c message.h
	$(CC) $(CFLAGS) $(MACROS) -c store.c

cache.o: cache.c message.h
	$(CC) $(CFLAGS) $(MACROS) -c cache.c

test_msg_store.o: test_msg_store.c message.h
	$(CC) $(CFLAGS) $(MACROS) -c test_msg_store.c

# Run the program
run: $(TARGET)
	./$(TARGET)

# Run automated test with Valgrind (optional)
valgrind: $(TARGET)
	@if command -v valgrind &> /dev/null; then \
		echo "Running Valgrind memory check..."; \
		valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET); \
	else \
		echo "Valgrind not found. Skipping memory check."; \
	fi

# Clean object files, binary, and message store
clean:
	rm -f $(OBJS) $(TARGET) message_store.bin

# Alias for testing everything: clean, build, run
test: clean all run

