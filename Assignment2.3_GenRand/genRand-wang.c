/*
 * genRand-wang.c / Assignment 2 - Random Number Generation
 *
 * ZW / CS5600 / Northeastern University
 * Fall 2025 / Sep 18, 2025
 *
 * Description:
 *   Generate N pseudo-random integers using a Linear Congruential Generator (LCG)
 *   and write them to a file. If "-a" is provided as a third argument, append
 *   to the file, otherwise overwrite.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Linear Congruential Generator (LCG) parameters
static unsigned long long seed = 1ULL;  // Initial seed

// Constants (same as used in glibc)
#define LCG_A 1664525
#define LCG_C 1013904223
#define LCG_M 4294967296UL  // 2^32

/*
 * Function: lcgRand
 * Generate next pseudo-random integer (full 32-bit range)
 */
unsigned int lcgRand() {
    seed = (LCG_A * seed + LCG_C) % LCG_M;
    return (unsigned int)seed;
}

/*
 * Function: genRand
 * Generate random integer in range [min, max]
 */
int genRand(int min, int max) {
    if (min > max) {
        // Swap if range is invalid
        int temp = min;
        min = max;
        max = temp;
    }
    unsigned int r = lcgRand();
    return (int)(min + (r % (max - min + 1)));
}

// Main Function
int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <count> <filename> [-a]\n", argv[0]);
        return 1;
    }

    // Parse arguments
    int count = atoi(argv[1]);         // number of random numbers
    char *filename = argv[2];          // output file name
    int append = (argc > 3 && strcmp(argv[3], "-a") == 0);

    // Seed the generator with current time
    seed = (unsigned long long)time(NULL);

    // Open file (append or overwrite mode)
    FILE *fp = fopen(filename, append ? "a" : "w");
    if (!fp) {
        perror("Error opening file");
        return 1;
    }

    // Generate and write random numbers
    for (int i = 0; i < count; i++) {
        int value = genRand(1, 100);  // Example: range 1–100
        fprintf(fp, "%d\n", value);
    }

    fclose(fp);

    printf("Generated %d random numbers %s %s\n",
           count,
           append ? "and appended to" : "into",
           filename);

    return 0;
}

