#!/bin/bash
# -------------------------------------------------------------------
# run_tests.sh
# Memory Hierarchy Simulation - Part II Automated Test Script
# Supports configurable cache size, number of messages, and accesses
# -------------------------------------------------------------------

CACHE_SIZE=${1:-16}
NUM_MESSAGES=${2:-50}
NUM_ACCESSES=${3:-1000}

echo "Cleaning and building project..."
make clean
make all CACHE_SIZE=$CACHE_SIZE NUM_MESSAGES=$NUM_MESSAGES NUM_ACCESSES=$NUM_ACCESSES

if [ $? -ne 0 ]; then
    echo "Build failed. Exiting."
    exit 1
fi

# Remove previous message store file
if [ -f message_store.bin ]; then
    rm -f message_store.bin
fi

echo "Running automated tests..."
echo "Configuration: CACHE_SIZE=$CACHE_SIZE, NUM_MESSAGES=$NUM_MESSAGES, NUM_ACCESSES=$NUM_ACCESSES"
./test_msg_store

# Optional memory leak check with Valgrind
if command -v valgrind &> /dev/null; then
    echo "Running memory check with Valgrind..."
    valgrind --leak-check=full --show-leak-kinds=all ./test_msg_store
else
    echo "Valgrind not found. Skipping memory leak check."
fi

echo "Test script completed."

