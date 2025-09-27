/*
* WangZ.CS5600.F25.c / Assignment 4 - Create Threads
*
* Zhimin Wang / CS5600 / Northeastern University
* Fall 2025 / Sep 27, 2025
*
* Description:
* Demonstrates creation and execution of multiple threads using POSIX pthreads.
* Includes a global array for thread communication: one thread writes unique values,
* the other reads them, showing shared memory between threads.
*
*
* TASK 4: Observation and Explanation of Thread Behavior
*
* Observations:
* - The Reader thread does not always read the values immediately after
*   the Writer thread writes them.
* - The order of printing is not strictly sequential due to the concurrent
*   execution of threads.
* - This demonstrates that shared memory access by multiple threads can
*   be non-deterministic without proper synchronization.
*
* Explanation:
* - In multi-threaded programs, the CPU scheduler decides which thread
*   runs at any given moment. Therefore, the Writer may write several
*   elements before the Reader gets CPU time to read them.
* - This can lead to inconsistencies or race conditions if threads
*   modify shared data without coordination.
*
* Potential Solution:
* - To avoid problems where threads "step on each other," synchronization
*   mechanisms are required. Common approaches include:
*   1. Mutex locks (pthread_mutex_t) to ensure that only one thread
*      accesses the shared array at a time.
*   2. Condition variables to signal between threads when data is ready
*      to be read.
* - Using these mechanisms would ensure data consistency and predictable
*   behavior in concurrent access scenarios. 
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define ARRAY_SIZE 10
 
// Global shared array for thread communication
int shared_array[ARRAY_SIZE];

// Worker function for writing data into the shared array
void *writer(void *data)
{
    char *name = (char*)data;

    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        shared_array[i] = i * 10; // Each element gets a unique value
        printf("Thread %s wrote %d to shared_array[%d]\n", name, shared_array[i], i);
        usleep(50000); // Sleep to simulate work
    }

    printf("Thread %s finished writing!\n", name);
    return NULL;
}

// Worker function for reading data from the shared array
void *reader(void *data)
{
    char *name = (char*)data;

    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        int value = shared_array[i]; // Read current value from shared array
        printf("Thread %s read %d from shared_array[%d]\n", name, value, i);
        usleep(70000); // Sleep to simulate work
    }

    printf("Thread %s finished reading!\n", name);
    return NULL;
}
 
int main(void)
{
    pthread_t th_writer, th_reader;

    // Initialize shared array with zeros
    for (int i = 0; i < ARRAY_SIZE; i++)
        shared_array[i] = 0;

    // Create writer and reader threads
    pthread_create(&th_writer, NULL, writer, "Writer");
    pthread_create(&th_reader, NULL, reader, "Reader");

    // Wait for both threads to finish
    pthread_join(th_writer, NULL);
    pthread_join(th_reader, NULL);

    printf("Exiting from main program\n");
    return 0;
}
