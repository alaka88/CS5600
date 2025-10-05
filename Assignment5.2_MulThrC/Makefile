# Makefile for Assignment 5
# ZW / CS5600 / Northeastern University
# Fall 2025 / Oct 4, 2025
#
# Description:
#   This Makefile compiles the multithreaded main program (main.c),
#   the Polybius cipher implementation (polybius.c),
#   and the random word generator (genRandWords-wang.c).


# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pthread

# Source files
MAIN_SRC = main.c queue.c polybius.c
GENRAND_SRC = genRandWords-wang.c

# Executables
MAIN_EXE = main
GENRAND_EXE = genRandWords-wang

# Default target: build everything
all: $(MAIN_EXE) $(GENRAND_EXE)

# Compile main multithreaded program
$(MAIN_EXE): $(MAIN_SRC) queue.h polybius.h
	$(CC) $(CFLAGS) -o $(MAIN_EXE) $(MAIN_SRC)

# Compile genRandWords program
$(GENRAND_EXE): $(GENRAND_SRC)
	$(CC) $(CFLAGS) -o $(GENRAND_EXE) $(GENRAND_SRC)

# Run automated tests
test: all
	@echo "Setting script executable..."
	chmod +x run_tests.sh
	@echo "Running automated tests..."
	./run_tests.sh

# Clean compiled executables and temporary files
clean:
	@echo "Cleaning up..."
	rm -f $(MAIN_EXE) $(GENRAND_EXE) output_*.txt *.o

