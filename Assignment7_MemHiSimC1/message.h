/*
* message.h / Memory Hierarchy Simulation - Part I
*
* Zhimin Wang / CS5600 / Northeastern University
* Fall 2025 / Oct 21, 2025
*
* Description:Defines the Message and Cache structures, and functions
*        for creating, storing, retrieving, and managing messages
*        in a message-oriented data store.
*/

#ifndef MESSAGE_H
#define MESSAGE_H


/* Structure representing a single message */
typedef struct {
    int id;                   /* Unique message identifier */
    char sender[50];          /* Name of the sender */
    char receiver[50];        /* Name of the receiver */
    char content[256];        /* Message content */
    char time_sent[20];       /* Timestamp when the message was created */
    int delivered;            /* Delivery status (0 = not delivered, 1 = delivered) */
} Message;

/* Structure representing a simple in-memory cache */
typedef struct {
    Message* messages[5];     /* Cache can hold up to 5 messages */
    int count;                /* Number of messages currently in cache */
} Cache;

/* Function declarations */
Message* create_msg(int id, const char* sender, const char* receiver, const char* content);
void store_msg(Message* msg, const char* filename);
Message* retrieve_msg_disk(int id, const char* filename);
Cache* create_cache();
void free_cache(Cache* cache);
void add_to_cache(Cache* cache, Message* msg);
Message* retrieve_msg(int id, Cache* cache, const char* filename);
void print_msg(Message* msg);

#endif
