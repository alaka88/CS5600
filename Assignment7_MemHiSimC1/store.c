/*
* store.c / Memory Hierarchy Simulation - Part I
*
* Zhimin Wang / CS5600 / Northeastern University
* Fall 2025 / Oct 21, 2025
*
* Memory Hierarchy Simulation - Disk Storage
*
* Functions: store_msg, retrieve_msg_disk
*/

#include <stdio.h>
#include <stdlib.h>
#include "message.h"

/* Store a message to disk */
void store_msg(Message* msg, const char* filename) {
    FILE* fp = fopen(filename, "ab");  // append in binary mode
    if (!fp) { printf("Failed to open file %s for writing.\n", filename); return; }
    fwrite(msg, sizeof(Message), 1, fp);
    fclose(fp);
}

/* Retrieve a message from disk by ID */
Message* retrieve_msg_disk(int id, const char* filename) {
    FILE* fp = fopen(filename, "rb");
    if (!fp) { printf("Failed to open file %s for reading.\n", filename); return NULL; }

    Message* msg = (Message*) malloc(sizeof(Message));
    if (!msg) { printf("Memory allocation failed.\n"); fclose(fp); return NULL; }

    while (fread(msg, sizeof(Message), 1, fp)) {
        if (msg->id == id) {
            fclose(fp);
            return msg;
        }
    }

    fclose(fp);
    free(msg);
    return NULL;  // not found
}
