/*
* message.c / Memory Hierarchy Simulation - Part I
*
* Zhimin Wang / CS5600 / Northeastern University
* Fall 2025 / Oct 21, 2025
*
* Memory Hierarchy Simulation - Cache Handling
*
* Functions: create_cache, free_cache, add_to_cache, retrieve_msg
*/

#include <stdio.h>
#include <stdlib.h>
#include "message.h"

/* Create a cache */
Cache* create_cache() {
    Cache* cache = (Cache*) malloc(sizeof(Cache));
    if (!cache) { printf("Memory allocation failed for cache.\n"); return NULL; }
    cache->count = 0;
    for (int i = 0; i < 5; i++) cache->messages[i] = NULL;
    return cache;
}

/* Free cache memory */
void free_cache(Cache* cache) {
    if (!cache) return;
    for (int i = 0; i < cache->count; i++) free(cache->messages[i]);
    free(cache);
}

/* Add a message to cache (FIFO replacement if full) */
void add_to_cache(Cache* cache, Message* msg) {
    if (!cache || !msg) return;
    if (cache->count < 5) cache->messages[cache->count++] = msg;
    else {
        free(cache->messages[0]);
        for (int i = 1; i < 5; i++) cache->messages[i-1] = cache->messages[i];
        cache->messages[4] = msg;
    }
}

/* Retrieve a message by ID from cache first, then disk */
Message* retrieve_msg(int id, Cache* cache, const char* filename) {
    if (cache) {
        for (int i = 0; i < cache->count; i++) {
            if (cache->messages[i]->id == id) return cache->messages[i];
        }
    }
    Message* msg = retrieve_msg_disk(id, filename);
    if (msg && cache) add_to_cache(cache, msg);
    return msg;
}
