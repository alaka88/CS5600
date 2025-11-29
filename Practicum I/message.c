/*
 * message.c / Memory Hierarchy Simulation - Part II
 *
 * Implements message creation, serialization, and simple
 * persistent storage and retrieval for a memory hierarchy simulator.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "message.h"

/* Create a new message dynamically */
Message* create_msg(int id, const char* sender, const char* receiver, const char* content) {
    Message* msg = malloc(sizeof(Message));
    if (!msg) {
        fprintf(stderr, "Memory allocation failed for message\n");
        exit(EXIT_FAILURE);
    }

    msg->id = id;
    strncpy(msg->sender, sender, sizeof(msg->sender) - 1);
    strncpy(msg->receiver, receiver, sizeof(msg->receiver) - 1);
    strncpy(msg->content, content, sizeof(msg->content) - 1);

    // Add timestamp
    snprintf(msg->time_sent, sizeof(msg->time_sent), "%ld", time(NULL));

    // Initialize other fields
    msg->delivered = 0;
    msg->last_access = 0;

    return msg;
}

/* Print message info */
void print_msg(const Message* msg) {
    if (!msg) {
        printf("(null message)\n");
        return;
    }

    printf("Message ID: %d\n", msg->id);
    printf("From: %s\n", msg->sender);
    printf("To: %s\n", msg->receiver);
    printf("Time: %s\n", msg->time_sent);
    printf("Delivered: %s\n", msg->delivered ? "Yes" : "No");
    printf("Content: %s\n", msg->content);
}

