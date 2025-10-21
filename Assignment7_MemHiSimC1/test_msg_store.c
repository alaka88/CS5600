/*
* test_msg_store.c / Memory Hierarchy Simulation - Part I
*
* Zhimin Wang / CS5600 / Northeastern University
* Fall 2025 / Oct 21, 2025
*
* Description:
* This program performs automated testing of the message store system,
* including cache operations, disk storage, retrieval, edge cases, and
* memory management. It tests FIFO cache replacement, retrieval of non-existent
* messages, and multiple inserts to ensure correctness.
*/

#include <stdio.h>
#include <stdlib.h>
#include "message.h"

#define FILENAME "message_store.bin"

int main() {
    printf("=== Automated Message Store Test ===\n");

    // Create cache
    Cache* cache = create_cache();
    if (!cache) {
        printf("Cache creation failed.\n");
        return 1;
    }

    // Clear previous disk file
    FILE* fp = fopen(FILENAME, "wb");
    if (fp) fclose(fp);

    // Insert 6 messages to test cache replacement (cache size = 5)
    for (int i = 1; i <= 6; i++) {
        char sender[20], receiver[20], content[50];
        snprintf(sender, sizeof(sender), "Sender%d", i);
        snprintf(receiver, sizeof(receiver), "Receiver%d", i);
        snprintf(content, sizeof(content), "Message content %d", i);

        Message* msg = create_msg(i, sender, receiver, content);
        store_msg(msg, FILENAME);
        add_to_cache(cache, msg);
    }

    // Test: retrieve messages 1-6
    for (int i = 1; i <= 6; i++) {
        Message* msg = retrieve_msg(i, cache, FILENAME);
        if (msg) {
            printf("\nRetrieved ID %d:\n", i);
            print_msg(msg);
        } else {
            printf("\nMessage ID %d not found (as expected if evicted from cache).\n", i);
        }
    }

    // Test: retrieve non-existent message
    Message* msg = retrieve_msg(99, cache, FILENAME);
    if (!msg) {
        printf("\nMessage ID 99 not found (edge case test passed).\n");
    }

    // Free cache
    free_cache(cache);

    printf("\n=== Automated Test Completed ===\n");

    return 0;
}
