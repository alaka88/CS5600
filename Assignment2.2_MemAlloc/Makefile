# Makefile for Assignment 2 - Memory Management
# ZW / Northeastern University
# 9/17/2025

CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Source files
ALLOC_SRC = alloc-mem-wang.c
LOAD_SRC  = load-mem-wang.c

# Targets
ALLOC_TARGET = allocmem
LOAD_TARGET  = loadmem

# Default target: build both
all: $(ALLOC_TARGET) $(LOAD_TARGET)

# Compile alloc-mem program
$(ALLOC_TARGET): $(ALLOC_SRC)
	$(CC) $(CFLAGS) -o $(ALLOC_TARGET) $(ALLOC_SRC)

# Compile load-mem program
$(LOAD_TARGET): $(LOAD_SRC)
	$(CC) $(CFLAGS) -o $(LOAD_TARGET) $(LOAD_SRC)

# Clean up executables
clean:
	rm -f $(ALLOC_TARGET) $(LOAD_TARGET) *.o
