/*
* queue.c / Assignment 5 - Multiprocessing in C
*
* ZW / CS5600 / Northeastern University
* Fall 2025 / Sep 30, 2025
*
* Description:
*   Implementation of a generic doubly-linked queue.
*   The queue stores void* data so it can hold any data type.
*   This file implements the functions declared in queue.h:
*     - add2q: add element to the tail of the queue
*     - popQ: remove and return data from the head of the queue
*     - rmProcess: find, remove, and return the process with highest priority
*     - qsize: return the number of elements in the queue
*/

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

/**
 * add2q
 * Adds an element to the end (tail) of the queue.
 * element can be any pointer type, including char* (words)
 */
void add2q(queue_t *queue, void *element) {
  if (!queue) {
    fprintf(stderr, "add2q: queue is NULL\n");
    return;
  }

  node_t *newNode = (node_t *)malloc(sizeof(node_t));
  if (!newNode) {
    fprintf(stderr, "add2q: memory allocation failed\n");
    exit(1);
  }

  newNode->data = element;
  newNode->next = NULL;
  newNode->prev = queue->tail;

  if (queue->tail) {
    /* there is an existing tail, link it to new node */
    queue->tail->next = newNode;
  } else {
    /* queue was empty, new node becomes head as well */
    queue->head = newNode;
  }

  /* update tail to new node and increment size */
  queue->tail = newNode;
  queue->size++;
}

/**
 * popQ
 * Removes and returns the data pointer from the front (head) of the queue.
 * Returns NULL if queue is empty.
 * Caller must free returned pointer if dynamically allocated (e.g., char* word)
 */
void *popQ(queue_t *queue) {
  if (!queue || queue->head == NULL) return NULL;

  node_t *front = queue->head;
  void *data = front->data;

  /* move head forward */
  queue->head = front->next;
  if (queue->head) {
    /* new head has no previous */
    queue->head->prev = NULL;
  } else {
    /* queue became empty */
    queue->tail = NULL;
  }

  free(front);      /* free the node structure */
  queue->size--;    /* update size */

  return data;
}

/**
 * qsize
 * Returns the number of elements currently in the queue.
 */
int qsize(queue_t *queue) {
  if (!queue) return 0;
  return queue->size;
}
