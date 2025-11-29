/*
* message.h / Memory Hierarchy Simulation - Part II
*
* Zhimin Wang / CS5600 / Northeastern University
* Fall 2025 / Oct 29, 2025
*
* Header defining Message structure, Cache structure, and function prototypes.
*/

#ifndef MESSAGE_H
#define MESSAGE_H

#include <stdio.h>

// ==============================
// Constants
// ==============================
#define MESSAGE_CONTENT_SIZE 256

// Cache replacement policy constants
#define CACHE_REPLACE_RANDOM 0
#define CACHE_REPLACE_FIFO   1
#define CACHE_REPLACE_LIFO   2

// ==============================
// Message structure
// ==============================
typedef struct {
    int id;                                 /* Unique message identifier */
    char sender[50];                        /* Sender name */
    char receiver[50];                      /* Receiver name */
    char content[MESSAGE_CONTENT_SIZE];     /* Message content */
    char time_sent[20];                     /* Timestamp when message was created */
    int delivered;                          /* Delivery status (0 = not delivered, 1 = delivered) */
    int last_access;                        /* Optional access counter (for replacement policies) */
} Message;

// ==============================
// Cache structure
// ==============================
typedef struct {
    Message** messages;     // dynamic array of message pointers
    int capacity;           // max number of messages in cache
    int count;              // current number of cached messages
    int replace_policy;     // replacement policy (random, FIFO, LIFO)
    int hits;               // number of cache hits
    int misses;             // number of cache misses
    int access_count;       // total number of cache lookups
    int fifo_index;         // for FIFO replacement tracking
} Cache;

// ==============================
// Function Prototypes
// ==============================

// message.c
Message* create_msg(int id, const char* sender, const char* receiver, const char* content);
void print_msg(const Message* msg);

// store.c
void store_msg(Message* msg, const char* filename);
Message* retrieve_msg_disk(int id, const char* filename);

// cache.c
Cache* create_cache(int capacity, int replace_policy);
void free_cache(Cache* cache);
void add_to_cache(Cache* cache, Message* msg);
Message* retrieve_msg(int id, Cache* cache, const char* filename);
void print_cache_stats(Cache* cache);

#endif  // MESSAGE_H

