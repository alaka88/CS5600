Zhimin Wang
CS5600
Overview
This project implements a simple message-oriented data store simulation in C, demonstrating aspects of hierarchical memory, disk storage, and in-memory caching. Messages can be created, stored to disk, retrieved from disk, cached in memory, and printed. The cache supports configurable replacement policies (Random, FIFO, LIFO) and configurable cache size.

File Structure

message.c           - Implementation of message creation, storage, cache, and retrieval
store.c             - Disk storage functions
cache.c             - In-memory cache functions
test_msg_store.c    - Test program for all functionalities
message_store.bin   - Binary file for storing messages (generated at runtime)
Makefile            - Build rules and automated test target
run_tests.sh        - Automated test script
README.txt          - This file

Cache Design Strategy

Purpose: Reduce disk accesses by storing frequently accessed messages in memory.
Replacement Policies:
Random: Randomly selects a message to evict when cache is full.
FIFO: Evicts the oldest message in the cache.
LIFO: Evicts the most recently added message in the cache.
Design Choice: Cache implemented as a dynamic array of Message* pointers. Keeps track of hits, misses, and access order. FIFO/LIFO policies use an index to determine which slot to replace.

Data Structures
Message: Contains id, sender, receiver, content.
Cache: Dynamic array of Message*, capacity, count, replacement policy, hit/miss counters, and access tracking.
Rationale: Dynamic array is simple and sufficient for small cache sizes; indexing supports efficient FIFO/LIFO replacement.

Page Replacement Algorithm
Random: Picks any message in the cache uniformly at random.
FIFO: Evicts the oldest cached message.
LIFO: Evicts the newest cached message.
Configurable: Policy is passed as a parameter when creating the cache.

Configurable Parameters
CACHE_SIZE: Number of messages the cache can hold. Default: 16
NUM_MESSAGES: Number of messages inserted during tests. Default: 50
NUM_ACCESSES: Number of message retrieval operations during testing. Default: 1000

How to Compile and Run
1. Make run_tests.sh executable (first time only)

chmod +x run_tests.sh

2. Compile all source files
make all

Default configuration:
CACHE_SIZE=16
NUM_MESSAGES=50
NUM_ACCESSES=1000

To customize cache size, number of messages, or number of accesses:
make all CACHE_SIZE=32 NUM_MESSAGES=100 NUM_ACCESSES=2000

This will create the executable test_msg_store.

3. Run automated tests
Option 1: Directly via Make
make run

Option 2: Using the test script
./run_tests.sh
To run the script with custom parameters:
./run_tests.sh 32 100 2000
Where the numbers correspond to CACHE_SIZE, NUM_MESSAGES, and NUM_ACCESSES respectively.

4. Expected Output

Program creates messages, stores them to disk, caches them in memory, and retrieves them.

Prints cache statistics for each replacement policy (Random, FIFO, LIFO): total accesses, hits, misses, hit ratio.

Example output:
Configuration: CACHE_SIZE=32, NUM_MESSAGES=100, NUM_ACCESSES=2000
--- Testing cache with Random replacement ---
Total accesses: 2000
Cache hits: 632
Cache misses: 1368
Cache hit ratio: 31.60%
...

Metrics (Example)
Metrics are collected for each cache replacement policy during automated testing:
Cache Hits: Number of times a message was found in cache
Cache Misses: Number of times a message was not in cache and loaded from disk
Cache Hit Ratio:Hit Ratio=(Cache Hits​/Total Accesses)×100%
| Replacement Policy | Total Accesses | Cache Hits | Cache Misses | Hit Ratio |
| ------------------ | -------------- | ---------- | ------------ | --------- |
| Random             | 1000           | 314        | 686          | 31.40%    |
| FIFO               | 1000           | 331        | 669          | 33.10%    |
| LIFO               | 1000           | 312        | 688          | 31.20%    |

Test Cases
Test Logic:
Insert NUM_MESSAGES messages into disk and cache.
Perform NUM_ACCESSES random retrievals of message IDs.
Cache is checked first; if miss, load from disk.
Replacement policies applied when cache is full.

Validation Points:
All inserted messages are retrievable from disk.
Cache hit/miss counts match expected behavior.
Replacement policy behaves correctly (Random, FIFO, LIFO).
Hit ratio calculations are correct:Cache Hits+Cache Misses=Total Accesses

5. How It Works
Message Creation: Dynamically allocates memory for each message.
Disk Storage: Appends messages to message_store.bin in binary mode.
Cache: Configurable size and replacement policy; stores messages in memory to speed up access.
Retrieval: Checks cache first, then disk if not found.
Testing: run_tests.sh automates inserting messages, performing accesses, and printing cache metrics.

6. Clean Build Artifacts
make clean
Deletes object files (*.o), the test_msg_store executable, and message_store.bin.