/*
* test_msg_store.c / Memory Hierarchy Simulation - Part II
*
* Zhimin Wang / CS5600 / Northeastern University
* Fall 2025 / Oct 29, 2025
*
* Description:
* Automated testing of message store system with cache metrics.
* Tests Random, FIFO, and LIFO replacement policies with configurable
* cache size, number of messages, and number of accesses.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "message.h"

#define FILENAME "message_store.bin"
// ==== Configurable parameters (use macros from Makefile if provided) ====
#ifndef CACHE_SIZE
#define CACHE_SIZE 16
#endif

#ifndef NUM_MESSAGES
#define NUM_MESSAGES 50
#endif

#ifndef NUM_ACCESSES
#define NUM_ACCESSES 1000
#endif

int main() {
    printf("=== Automated Message Store Test (Part II) ===\n");
    printf("Configuration: CACHE_SIZE=%d, NUM_MESSAGES=%d, NUM_ACCESSES=%d\n",
           CACHE_SIZE, NUM_MESSAGES, NUM_ACCESSES);

    // Clear previous disk file
    FILE* fp = fopen(FILENAME, "wb");
    if (fp) fclose(fp);

    // Insert NUM_MESSAGES messages
    for (int i = 1; i <= NUM_MESSAGES; i++) {
        char sender[50], receiver[50], content[256];
        snprintf(sender, sizeof(sender), "Sender%d", i);
        snprintf(receiver, sizeof(receiver), "Receiver%d", i);
        snprintf(content, sizeof(content), "Message content %d", i);

        Message* msg = create_msg(i, sender, receiver, content);
        store_msg(msg, FILENAME);
        free(msg);  // free after storing to disk
    }

    // Test all replacement policies
    int policies[3] = {CACHE_REPLACE_RANDOM, CACHE_REPLACE_FIFO, CACHE_REPLACE_LIFO};
    const char* policy_names[3] = {"Random", "FIFO", "LIFO"};

    for (int p = 0; p < 3; p++) {
        printf("\n--- Testing cache with %s replacement ---\n", policy_names[p]);

        Cache* cache = create_cache(CACHE_SIZE, policies[p]);
        if (!cache) {
            printf("Cache creation failed.\n");
            return 1;
        }

        srand((unsigned int) time(NULL));

        // Perform NUM_ACCESSES random message retrievals
        for (int i = 0; i < NUM_ACCESSES; i++) {
            int id = (rand() % NUM_MESSAGES) + 1;
            Message* msg = retrieve_msg(id, cache, FILENAME);
            if (!msg) {
                printf("Error: Message ID %d not found on disk.\n", id);
            }
        }

        // Print cache performance metrics
        print_cache_stats(cache);

        free_cache(cache);
    }

    printf("\n=== Automated Test Completed ===\n");
    return 0;
}

