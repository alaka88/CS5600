/*
* message.h / Memory Hierarchy Simulation - Part II
*
* Zhimin Wang / CS5600 / Northeastern University
* Fall 2025 / Oct 29, 2025
*
* Description:
* Defines the Message and Cache structures, and functions
* for creating, storing, retrieving, and managing messages
* with a dynamic, configurable cache supporting page replacement.
*/

#ifndef MESSAGE_H
#define MESSAGE_H

/* Configurable message content size */
#define MESSAGE_CONTENT_SIZE 256

/* Structure representing a single message */
typedef struct {
    int id;                                 /* Unique message identifier */
    char sender[50];                        /* Name of the sender */
    char receiver[50];                      /* Name of the receiver */
    char content[MESSAGE_CONTENT_SIZE];     /* Message content */
    char time_sent[20];                      /* Timestamp when the message was created */
    int delivered;                           /* Delivery status (0 = not delivered, 1 = delivered) */
    int last_access;                         /* Last access counter for replacement algorithms (optional for LRU) */
} Message;

/* Cache replacement policies */
#define CACHE_REPLACE_RANDOM 0
#define CACHE_REPLACE_FIFO   1
#define CACHE_REPLACE_LIFO   2

/* Structure representing a dynamic in-memory cache */
typedef struct {
    Message** messages;       /* Dynamic array of pointers to messages */
    int capacity;             /* Maximum number of messages in cache */
    int count;                /* Current number of messages in cache */
    int replace_policy;       /* Replacement policy: RANDOM, FIFO, or LIFO */
    int hits;                 /* Number of cache hits */
    int misses;               /* Number of cache misses */
    int access_count;         /* Total number of cache accesses */
} Cache;

/* Function declarations */

/* Message operations */
Message* create_msg(int id, const char* sender, const char* receiver, const char* content);
void store_msg(Message* msg, const char* filename);
Message* retrieve_msg_disk(int id, const char* filename);
void print_msg(Message* msg);

/* Cache operations */
Cache* create_cache(int capacity, int replace_policy);
void free_cache(Cache* cache);
void add_to_cache(Cache* cache, Message* msg);
Message* retrieve_msg(int id, Cache* cache, const char* filename);
void print_cache_stats(Cache* cache);

#endif /* MESSAGE_H */

