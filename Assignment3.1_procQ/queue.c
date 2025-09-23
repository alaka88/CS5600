/*
* queue.c / Assignment 3 - Implement Process Queue
*
* ZW / CS5600 / Northeastern University
* Fall 2025 / Sep 23, 2025
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
 * If queue is NULL the function returns silently.
 * The function allocates a new node_t and links it at the tail.
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
 * If queue is NULL or empty, returns NULL.
 * The node memory is freed; the returned data pointer remains valid and
 * must be freed by the caller if it was dynamically allocated.
 */
void *popQ(queue_t *queue) {
  if (!queue) {
    fprintf(stderr, "popQ: queue is NULL\n");
    return NULL;
  }

  if (queue->head == NULL) {
    /* queue empty */
    return NULL;
  }

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
 * rmProcess
 * Finds, removes, and returns the process_t* with the highest priority.
 * If queue is NULL or empty, returns NULL.
 * Assumes each node's data is a process_t*; does not free the returned data.
 * If multiple processes have the same highest priority, the first encountered
 * (closest to head) is removed and returned.
 */
process_t *rmProcess(queue_t *queue) {
  if (!queue) {
    fprintf(stderr, "rmProcess: queue is NULL\n");
    return NULL;
  }

  if (queue->head == NULL) {
    /* queue empty */
    return NULL;
  }

  node_t *current = queue->head;
  node_t *bestNode = current;
  process_t *bestProc = (process_t *)current->data;

  /* traverse the queue to find the node with maximum priority */
  while (current) {
    process_t *proc = (process_t *)current->data;
    if (proc->priority > bestProc->priority) {
      bestNode = current;
      bestProc = proc;
    }
    current = current->next;
  }

  /* unlink bestNode from the list */
  if (bestNode->prev) {
    bestNode->prev->next = bestNode->next;
  } else {
    /* bestNode was head */
    queue->head = bestNode->next;
  }

  if (bestNode->next) {
    bestNode->next->prev = bestNode->prev;
  } else {
    /* bestNode was tail */
    queue->tail = bestNode->prev;
  }

  free(bestNode);  /* free the node struct only */
  queue->size--;   /* update size */

  return bestProc; /* caller owns the returned process pointer */
}

/**
 * qsize
 * Returns the number of elements currently in the queue.
 * If queue is NULL, returns 0.
 */
int qsize(queue_t *queue) {
  if (!queue) return 0;
  return queue->size;
}
