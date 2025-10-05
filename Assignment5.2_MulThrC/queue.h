/*
* queue.h / Assignment 5 - Multithreading in C
*
* ZW / CS5600 / Northeastern University
* Fall 2025 / Oct 4, 2025
*
* Description:
 * Node structure
 * Represents a node in the doubly-linked queue.
 * Stores a void* so that it can hold any data type, e.g., char* (words) 
*/

#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>


/**
 * Node structure
 * Represents a node in the doubly-linked queue.
 * Stores a void* so that it can hold any data type, e.g., char* (words)
 */
typedef struct node {
    void *data;          // Pointer to the data (can be any type)
    struct node *next;   // Pointer to the next node
    struct node *prev;   // Pointer to the previous node
} node_t;

/**
 * Queue structure
 * Represents a generic queue implemented as a doubly-linked list.
 */
typedef struct {
    node_t *head;   // Pointer to the front of the queue
    node_t *tail;   // Pointer to the end of the queue
    int size;       // Number of elements in the queue
} queue_t;

/**
 * Adds an element to the end of the queue.
 * - element: pointer to any data type
 */
void add2q(queue_t *queue, void *element);

/**
 * Removes and returns the data from the front of the queue.
 * Returns NULL if the queue is empty.
 * Caller must free the returned data if it was dynamically allocated (e.g., char*).
 */
void *popQ(queue_t *queue);

/**
 * Returns the number of elements in the queue.
 */
int qsize(queue_t *queue);

#endif // QUEUE_H
