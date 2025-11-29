/*
* cache.c / Memory Hierarchy Simulation - Part II
*
* Zhimin Wang / CS5600 / Northeastern University
* Fall 2025 / Oct 29, 2025
*
* Memory Hierarchy Simulation - Cache Handling
*
* Functions: create_cache, free_cache, add_to_cache, retrieve_msg, print_cache_stats
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "message.h"

/* Create a cache with configurable capacity and replacement policy */
Cache* create_cache(int capacity, int replace_policy) {
    Cache* cache = (Cache*) malloc(sizeof(Cache));
    if (!cache) {
        printf("Memory allocation failed for cache.\n");
        return NULL;
    }

    cache->messages = (Message**) calloc(capacity, sizeof(Message*));
    if (!cache->messages) {
        printf("Memory allocation failed for cache messages array.\n");
        free(cache);
        return NULL;
    }

    cache->capacity = capacity;
    cache->count = 0;
    cache->replace_policy = replace_policy;
    cache->hits = 0;
    cache->misses = 0;
    cache->access_count = 0;
    cache->fifo_index = 0;  // initialize FIFO index

    srand((unsigned int) time(NULL));  // seed for Random replacement
    return cache;
}

/* Free cache memory */
void free_cache(Cache* cache) {
    if (!cache) return;

    for (int i = 0; i < cache->count; i++) {
        if (cache->messages[i]) free(cache->messages[i]);
    }
    free(cache->messages);
    free(cache);
}

/* Add a message to cache with page replacement */
void add_to_cache(Cache* cache, Message* msg) {
    if (!cache || !msg) return;

    // If cache is not full, just add to next free slot
    if (cache->count < cache->capacity) {
        cache->messages[cache->count++] = msg;
        return;
    }

    int idx = 0;

    // Choose victim index based on policy
    switch (cache->replace_policy) {
        case CACHE_REPLACE_RANDOM:
            idx = rand() % cache->capacity;
            break;
        case CACHE_REPLACE_LIFO:
            idx = cache->count - 1;  // replace most recently added
            break;
        case CACHE_REPLACE_FIFO:
            idx = cache->fifo_index; // replace the oldest message
            cache->fifo_index = (cache->fifo_index + 1) % cache->capacity;
            break;
        default:
            idx = 0; // fallback
            break;
    }

    // Replace message
    free(cache->messages[idx]);
    cache->messages[idx] = msg;
}

/* Retrieve a message by ID from cache first, then disk */
Message* retrieve_msg(int id, Cache* cache, const char* filename) {
    if (!cache) return retrieve_msg_disk(id, filename);

    cache->access_count++;

    // Search cache first
    for (int i = 0; i < cache->count; i++) {
        if (cache->messages[i] && cache->messages[i]->id == id) {
            cache->hits++;
            return cache->messages[i];
        }
    }

    // Not in cache → fetch from disk
    Message* msg = retrieve_msg_disk(id, filename);
    if (msg) {
        cache->misses++;
        add_to_cache(cache, msg);
    } else {
        cache->misses++;
    }

    return msg;
}

/* Print cache performance metrics */
void print_cache_stats(Cache* cache) {
    if (!cache) return;

    double ratio = (cache->access_count == 0) ? 0.0
                 : ((double) cache->hits / cache->access_count) * 100.0;

    printf("\n=== Cache Statistics ===\n");
    printf("Total accesses: %d\n", cache->access_count);
    printf("Cache hits: %d\n", cache->hits);
    printf("Cache misses: %d\n", cache->misses);
    printf("Cache hit ratio: %.2f%%\n", ratio);
    printf("========================\n");
}

