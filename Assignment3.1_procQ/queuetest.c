/*
* queuetest.c / Assignment 3 - Implement Process Queue
*
* ZW / CS5600 / Northeastern University
* Fall 2025 / Sep 23, 2025
 * Description:
 *   Test program for the generic doubly-linked queue implemented in queue.c/h.
 *
 *   The program creates multiple process_t instances, adds them to the queue,
 *   prints the queue contents between steps, and checks expected behavior.
*
*/

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

/**
 * Helper: print the contents of the queue.
 * Assumes the queue holds process_t* elements.
 */
void print_queue(queue_t *queue) {
  printf("Queue [size=%d]:\n", qsize(queue));
  node_t *current = queue->head;
  while (current) {
    process_t *proc = (process_t *)current->data;
    printf("  [ID=%d, Name=%s, RunTime=%ld, Priority=%d]\n",
           proc->id, proc->name, proc->run_time, proc->priority);
    current = current->next;
  }
  printf("\n");
}

int main() {
  // Create an empty queue
  queue_t q = { NULL, NULL, 0 };
  printf("Created an empty queue.\n");
  print_queue(&q);

  // Add three processes
  process_t *p1 = malloc(sizeof(process_t));
  p1->id = 1; p1->name = "Process1"; p1->run_time = 50; p1->priority = 2;
  add2q(&q, p1);

  process_t *p2 = malloc(sizeof(process_t));
  p2->id = 2; p2->name = "Process2"; p2->run_time = 30; p2->priority = 5;
  add2q(&q, p2);

  process_t *p3 = malloc(sizeof(process_t));
  p3->id = 3; p3->name = "Process3"; p3->run_time = 40; p3->priority = 1;
  add2q(&q, p3);

  printf("Added three processes to the queue.\n");
  print_queue(&q);

  // Pop one process from the front
  process_t *front = (process_t *)popQ(&q);
  printf("Popped front process: [ID=%d, Name=%s]\n", front->id, front->name);
  free(front);
  print_queue(&q);

  // Remove process with highest priority
  process_t *best = rmProcess(&q);
  printf("Removed highest priority process: [ID=%d, Name=%s, Priority=%d]\n",
         best->id, best->name, best->priority);
  free(best);
  print_queue(&q);

  // Add another process
  process_t *p4 = malloc(sizeof(process_t));
  p4->id = 4; p4->name = "Process4"; p4->run_time = 60; p4->priority = 10;
  add2q(&q, p4);

  printf("Added another process (Process4).\n");
  print_queue(&q);

  // Clean up remaining processes
  while (qsize(&q) > 0) {
    process_t *p = (process_t *)popQ(&q);
    printf("Cleaning up: freeing [ID=%d, Name=%s]\n", p->id, p->name);
    free(p);
  }

  printf("Queue is now empty.\n");
  print_queue(&q);

  return 0;
}

