#!/bin/bash
# -----------------------------------------------------------------------------
# run_tests.sh
#
# Memory Hierarchy Simulation - Automated Test Script
#
# Author: Zhimin Wang / CS5600 / Northeastern University
# Fall 2025 / Oct 21, 2025
#
# Description:
# This script compiles all C source files, runs the automated message store
# tests, and optionally checks for memory leaks using valgrind. It provides
# a complete automated workflow for verifying correct functionality of the
# message creation, caching, disk storage, and retrieval system.
#
# Usage:
#   chmod +x run_tests.sh
#   ./run_tests.sh
#
# Requirements:
#   - gcc (C11)
#   - valgrind (optional, for memory leak detection)
# -----------------------------------------------------------------------------

# Compilation
echo "Compiling all source files..."
gcc -Wall -Wextra -std=c11 -g -c message.c
gcc -Wall -Wextra -std=c11 -g -c store.c
gcc -Wall -Wextra -std=c11 -g -c cache.c
gcc -Wall -Wextra -std=c11 -g -c test_msg_store.c

# Link
gcc -Wall -Wextra -std=c11 -g -o test_msg_store message.o store.o cache.o test_msg_store.o

# Run automated tests
echo "Running automated tests..."
./test_msg_store

# Optional: Run valgrind memory check
if command -v valgrind &> /dev/null
then
    echo "Running memory check with Valgrind..."
    valgrind --leak-check=full --show-leak-kinds=all ./test_msg_store
else
    echo "Valgrind not found. Skipping memory leak check."
fi

echo "Test script completed."
