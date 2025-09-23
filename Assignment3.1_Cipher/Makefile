# Makefile for Assignment 3 - Create Cipher
# ZW / Northeastern University
# Fall 2025 / Sep 23，2025
# This Makefile compiles polybius.c and cipher.c into an executable "cipher"

CC = gcc           # the compiler to use
CFLAGS = -Wall -g  # compiler flags: show all warnings, enable debugging

# Target executable
TARGET = cipher

# Object files
OBJS = polybius.o cipher.o

# Default target
all: $(TARGET)

# Rule to build the target
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile polybius.c
polybius.o: polybius.c polybius.h
	$(CC) $(CFLAGS) -c polybius.c

# Rule to compile cipher.c
cipher.o: cipher.c polybius.h
	$(CC) $(CFLAGS) -c cipher.c

# Clean up build files
clean:
	rm -f $(TARGET) $(OBJS)
