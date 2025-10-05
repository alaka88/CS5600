# Makefile for Assignment 5
# ZW / CS5600 / Northeastern University
# Fall 2025 / Sep 30, 2025
#
# Description:
#   This Makefile compiles the main program (main.c) and the Polybius
#   cipher program (cipher.c / polybius.c) into executables.
#   It also provides targets for cleaning up compiled files and running
#   automated tests using run_tests.sh.

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99

# Source files
MAIN_SRC = main.c queue.c
CIPHER_SRC = cipher.c polybius.c
GENRAND_SRC = genRandWords-wang.c

# Executables
MAIN_EXE = main
CIPHER_EXE = cipher
GENRAND_EXE = genRandWords-wang

# Default target: build everything
all: $(MAIN_EXE) $(CIPHER_EXE) $(GENRAND_EXE)

# Compile main program
$(MAIN_EXE): $(MAIN_SRC) queue.h
	$(CC) $(CFLAGS) -o $(MAIN_EXE) $(MAIN_SRC)

# Compile cipher program
$(CIPHER_EXE): $(CIPHER_SRC) polybius.h
	$(CC) $(CFLAGS) -o $(CIPHER_EXE) $(CIPHER_SRC)

# Compile genRandWords program
$(GENRAND_EXE): $(GENRAND_SRC)
	$(CC) $(CFLAGS) -o $(GENRAND_EXE) $(GENRAND_SRC)

# Run automated tests
# Usage: make test
# This will build all programs first, then run the test script
test: all
	@echo "Running automated tests..."
	./run_tests.sh

# Clean compiled executables and temporary files
clean:
	@echo "Cleaning up..."
	rm -f $(MAIN_EXE) $(CIPHER_EXE) $(GENRAND_EXE) output_*.txt *.o test_results.log
