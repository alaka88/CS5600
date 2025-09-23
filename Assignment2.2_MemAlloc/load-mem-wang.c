/*
 * load-mem-wang.c / Assignment 2 - Memory Management
 *
 * ZW / CS5600 / Northeastern University
 * Fall 2025 / Sep 17, 2025
 *
 * Description:
 *   Demonstrates dynamic memory structures in C.
 *   1) Defines a dynBlock struct for dynamic arrays.
 *   2) allocDynBlock() allocates memory for a dynBlock.
 *   3) storeMem2Blk() stores integers into a dynBlock.
 *   4) Reads integers from blocks.data (each line → one dynBlock).
 *   5) Prints the loaded data to verify correctness.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024   // Maximum characters per line

/* 
 * Structure: dynBlock
 * --------------------
 * Stores an integer array dynamically allocated on the heap.
 */
typedef struct {
    int *data;      // Pointer to dynamically allocated integer array
    int size;       // Number of elements in the array
} dynBlock;

/*
 * Function: allocDynBlock
 * -----------------------
 * Allocates memory for a dynBlock and its integer array.
 *
 * size: number of integers to allocate
 *
 * returns: pointer to the newly allocated dynBlock
 */
dynBlock* allocDynBlock(int size) {
    dynBlock *block = (dynBlock*)malloc(sizeof(dynBlock));  // Allocate structure itself
    if (!block) {
        perror("Failed to allocate dynBlock");
        exit(1);
    }

    block->data = (int*)malloc(size * sizeof(int));  // Allocate integer array
    if (!block->data) {
        perror("Failed to allocate integer array");
        free(block);
        exit(1);
    }

    block->size = size;  // Store array size
    return block;
}

/*
 * Function: storeMem2Blk
 * ----------------------
 * Copies an array of integers into a dynBlock.
 *
 * block: pointer to a dynBlock
 * array: integers to copy
 * size: number of integers to copy
 */
void storeMem2Blk(dynBlock *block, int *array, int size) {
    if (!block || !block->data) {
        fprintf(stderr, "Error: invalid dynBlock in storeMem2Blk\n");
        return;
    }
    if (size > block->size) {
        fprintf(stderr, "Error: too many integers for this block\n");
        return;
    }

    memcpy(block->data, array, size * sizeof(int));
    block->size = size;  // update size 
}

/*
 * Function: printDynBlock
 * -----------------------
 * Prints the contents of a dynBlock.
 */
void printDynBlock(const dynBlock *block) {
    if (!block) return;
    printf("dynBlock with %d integers: ", block->size);
    for (int i = 0; i < block->size; i++) {
        printf("%d ", block->data[i]);
    }
    printf("\n");
}

/*
 * Function: freeDynBlock
 * ----------------------
 * Frees memory used by a dynBlock.
 */
void freeDynBlock(dynBlock *block) {
    if (!block) return;
    free(block->data);
    free(block);
}

/*
 * Function: main
 * --------------
 * Reads integers from blocks.data, stores each line
 * into a separate dynBlock, prints contents, then frees memory.
 */
int main() {
    FILE *fp = fopen("blocks.data", "r");
    if (!fp) {
        perror("Failed to open blocks.data");
        return 1;
    }

    char line[MAX_LINE];
    int blockCount = 0;

    while (fgets(line, sizeof(line), fp)) {
        int numbers[256];
        int count = 0;

        /* parse integers from line */
        char *token = strtok(line, " \t\n");
        while (token) {
            numbers[count++] = atoi(token);
            token = strtok(NULL, " \t\n");
        }

        /* allocate dynBlock and store numbers */
        dynBlock *block = allocDynBlock(count);
        storeMem2Blk(block, numbers, count);

        /* print for verification */
        printf("Block %d loaded: ", ++blockCount);
        printDynBlock(block);

        /* free memory for this block */
        freeDynBlock(block);
    }

    fclose(fp);
    printf("Finished reading all lines into dynamic blocks.\n");
    return 0;
}
