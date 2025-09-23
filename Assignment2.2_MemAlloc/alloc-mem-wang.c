/*
 * alloc-mem-wang.c / Assignment 2 - Memory Management
 *
 * ZW / CS5600 / Northeastern University
 * Fall 2025 / Sep 17, 2025
 *
 * Description:
 *   Demonstrates memory allocation in C: stack, heap, and static memory.
 *   This program demonstrates memory allocation and deallocation, and explains
 *   what happens to each memory segment when the program exits.
 *   - Heap: dynamically allocated memory using malloc/free
 *   - Stack: automatically allocated memory inside functions
 *   - Static: memory allocated in the static segment
 */

#include <stdio.h>
#include <stdlib.h> 

// Define memory sizes
#define HEAP_SIZE (10*1024*1024)   // 10 MB 
#define STACK_SIZE (1*1024*1024)    // 1 MB
#define STATIC_SIZE (5*1024*1024)  // 5 MB 

// ===============================
// Static memory allocation (static segment)
// Allocated at program start and automatically freed when program exits
// ===============================
static char staticArray[STATIC_SIZE]; // 5 MB static memory

int main() {
    // ===============================
    // Heap memory allocation
    // Allocated dynamically from the heap
    // Must be freed manually
    // ===============================
    char *heapArray = (char *)malloc(HEAP_SIZE);  // Allocate 10 MB from heap
    if (heapArray == NULL) {                         // Check allocation success
        perror("Heap allocation failed");            // Print system error
        return 1;                                    // Exit with error code
    }
    printf("Heap memory allocated: %d MB\n", HEAP_SIZE / (1024*1024)); // Print allocated size

    // ===============================
    // Stack memory allocation
    // Allocated automatically on function call
    // Freed automatically when main() returns
    // ===============================
    char stackArray[STACK_SIZE];   // 1 MB local array
    printf("Stack memory allocated: %d MB\n", STACK_SIZE / (1024*1024));

    // ===============================
    // Static memory usage
    // ===============================
    printf("Static memory allocated: %d MB\n", STATIC_SIZE / (1024*1024));

    // ===============================
    // Optional: use memory (fill with data)
    // ===============================
    for (int i = 0; i < 10; i++) {
        heapArray[i] = (char)(i + 65);     // Fill first 10 bytes with A-J
        stackArray[i] = (char)(i + 97);    // Fill first 10 bytes with a-j
        staticArray[i] = (char)(i + 48);   // Fill first 10 bytes with 0-9
    }
    printf("Memory blocks initialized.\n");
    // ===============================
    // Free heap memory
    // Return dynamically allocated memory to the operating system
    // ===============================
    free(heapArray);  
    printf("Heap memory freed.\n");

    // Stack memory and static memory are automatically freed when program exits
    printf("Program finished. Stack and static memory are automatically reclaimed on exit.\n");

    return 0;  
}
