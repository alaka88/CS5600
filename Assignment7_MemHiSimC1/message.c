/*
* message.c / Memory Hierarchy Simulation - Part I
*
* Zhimin Wang / CS5600 / Northeastern University
* Fall 2025 / Oct 21, 2025
*
* Description: Memory Hierarchy Simulation - Message Handling
*
* Functions: create_msg, print_msg
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "message.h"

/* Create a new message dynamically */
Message* create_msg(int id, const char* sender, const char* receiver, const char* content) {
    Message* msg = (Message*) malloc(sizeof(Message));
    if (!msg) { printf("Memory allocation failed.\n"); return NULL; }
    msg->id = id;
    strncpy(msg->sender, sender, sizeof(msg->sender));
    strncpy(msg->receiver, receiver, sizeof(msg->receiver));
    strncpy(msg->content, content, sizeof(msg->content));
    msg->delivered = 0;

    time_t t = time(NULL);
    struct tm tm_info = *localtime(&t);
    strftime(msg->time_sent, sizeof(msg->time_sent), "%Y-%m-%d %H:%M:%S", &tm_info);

    return msg;
}

/* Print message details */
void print_msg(Message* msg) {
    if (!msg) return;
    printf("ID: %d\nSender: %s\nReceiver: %s\nContent: %s\nTime Sent: %s\nDelivered: %d\n",
           msg->id, msg->sender, msg->receiver, msg->content, msg->time_sent, msg->delivered);
}
