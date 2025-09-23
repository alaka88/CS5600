/*
* queue.h / Assignment 3 - Implement Process Queue
*
* ZW / CS5600 / Northeastern University
* Fall 2025 / Sep 23, 2025
* Description:
* This file declares the data structures and functions for a generic
* queue implemented as a doubly-linked list. It also defines a process_t
* struct for representing a process with ID, name, cumulative run-time,
* and priority.
*
*/

#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>

/**
 * Process structure
 * Represents a process in the system.
 */
typedef struct {
    int id;           // Process identifier
    char *name;       // Process name
    long run_time;    // Cumulative run-time
    int priority;     // Priority of the process
} process_t;

/**
 * Node structure
 * Represents a node in the doubly-linked queue.
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
 */
void *popQ(queue_t *queue);

/**
 * Removes and returns the process with the highest priority.
 * Only works for queue containing process_t elements.
 * Returns NULL if the queue is empty.
 */
process_t *rmProcess(queue_t *queue);

/**
 * Returns the number of elements in the queue.
 * Returns 0 if the queue is empty.
 */
int qsize(queue_t *queue);

#endif // QUEUE_H
