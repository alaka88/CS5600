/*
 * genRandWords-wang.c / Assignment 5 - Multithreading in C 
 *
 * ZW / CS5600 / Northeastern University
 * Fall 2025 / Oct 4, 2025
 *
 * Description:
 *   Generate N pseudo-random words using a Linear Congruential Generator (LCG)
 *   and write them to a file. Each word has random length between 3 and 8 letters.
 *   The file must contain at least 10,000 words. If "-a" is provided as a third
 *   argument, words are appended to the file; otherwise the file is overwritten.
 *   
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

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

/*
 * Function: genRandomWord
 * 
 * Generate a random word of length between minLen and maxLen.
 * All letters are lowercase a-z.
 * Returns a malloc'ed string; caller must free it.
 */
char* genRandomWord(int minLen, int maxLen) {
    int len = genRand(minLen, maxLen);
    char *word = (char*)malloc(len + 1);
    if (!word) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    for (int i = 0; i < len; i++) {
        word[i] = 'a' + genRand(0, 25);  // random lowercase letter
    }
    word[len] = '\0';
    return word;
}


// Main Function
int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <word_count> <filename> [-a]\n", argv[0]);
        return 1;
    }

    int count = atoi(argv[1]);       // number of words to generate
    char *filename = argv[2];        // output file name
    int append = (argc > 3 && strcmp(argv[3], "-a") == 0);  // append mode

    // Seed the generator with current time
    seed = (unsigned long long)time(NULL);

    // Open file for writing/appending
    FILE *fp = fopen(filename, append ? "a" : "w");
    if (!fp) {
        perror("Error opening file");
        return 1;
    }

    // Generate and write random words
    for (int i = 0; i < count; i++) {
        char *word = genRandomWord(3, 8);  // word length 3-8
        fprintf(fp, "%s\n", word);         // write word to file
        free(word);                        // free malloc'ed memory
    }

    fclose(fp);

    printf("Generated %d random words %s %s\n",
           count,
           append ? "and appended to" : "into",
           filename);

    return 0;
}
