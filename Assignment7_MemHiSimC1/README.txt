Overview
This project implements a simple message-oriented data store simulation in C, demonstrating aspects of hierarchical memory, disk storage, and in-memory caching. Messages can be created, stored to disk, retrieved from disk, cached in memory, and printed. The cache uses a FIFO replacement policy and can hold up to 5 messages.

This project fulfills the requirements for CS5600 Fall 2025 Assignment.

File Structure

message.c           - Implementation of message creation, storage, cache, and retrieval
store.c             - Disk storage functions
cache.c             - In-memory cache functions
test_msg_store.c    - Test program for all functionalities
message_store.bin   - Binary file for storing messages (generated at runtime)
Makefile            - Build rules and automated test target
run_tests.sh        - Automated test script
README.txt          - This file

Notes:
- All files are in the same folder (no include/ folder required).
- message_store.bin is created automatically when running tests.

How to Compile and Run

1. Compile with Make
Open a terminal in the project directory:

chmod +x run_tests.sh   # Make the test script executable (first time only)
make                     # Compile all source files and generate test executable

This will create test_msg_store executable.

2. Run Automated Test
You can run the automated test either via Make or directly:

make run                # Runs the test program
or
./run_tests.sh          # Runs the automated test script

3. Expected Output
- The program will create several messages, store them on disk, cache them, and retrieve them.
- It will print each message’s details: ID, Sender, Receiver, Content, Timestamp, Delivered status.
- It tests cache retrieval, disk retrieval, and edge case handling (querying a non-existent ID).

How It Works
1. Message Creation: Dynamically allocates memory for each message.
2. Disk Storage: Stores messages in message_store.bin using binary append mode.
3. Cache: Holds up to 5 messages in memory; oldest message replaced if full.
4. Retrieval: Checks cache first, then disk.
5. Testing: Automated script (run_tests.sh) tests all functionality and edge cases.

4. make clean         # Delete all object (*.o) files and the test_msg_store executable file.
