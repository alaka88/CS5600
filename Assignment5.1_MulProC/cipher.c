/*
* cipher.c / Assignment 5 - Multiprocessing in C
*
* ZW / CS5600 / Northeastern University
* Fall 2025 / Sep 30, 2025
*
* Description:
*   This allows a parent process to spawn this program
*   as a child process, send multiple words via a pipe, and receive
*   encrypted output.
*
*   Usage examples:
*     ./cipher -e "this is plain text"   --> encrypts plaintext
*     ./cipher -d "ciphertext"           --> decrypts ciphertext
*     ./cipher -s                        --> read multiple words from stdin, one batch at a time
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "polybius.h"

#define MAX_LINE 1024

int main(int argc, char *argv[]) {
    polybius_table_t table;
    initTable(&table);  // create Polybius square

    // Batch mode: read from stdin
    if (argc == 2 && strcmp(argv[1], "-s") == 0) {
        char buffer[MAX_LINE];
        while (fgets(buffer, sizeof(buffer), stdin)) {
            // Remove trailing newline
            buffer[strcspn(buffer, "\n")] = '\0';

            // Skip empty lines
            if (strlen(buffer) == 0) continue;

            // Encrypt the line
            char *encoded = pbEncode(buffer, &table);
            if (encoded) {
                printf("%s\n", encoded);  // output to stdout
                free(encoded);
            } else {
                fprintf(stderr, "Encryption failed for line: %s\n", buffer);
            }
        }
        return 0;
    }
    
    // Original command-line mode
    if (argc < 3) {
        printf("Usage: %s -e \"text\" | -d \"cipher\"\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "-e") == 0) {
        /* Encrypt mode */
        char *encoded = pbEncode(argv[2], &table);
        if (encoded) {
            printf("Encrypted: %s\n", encoded);
            free(encoded);
        } else {
            printf("Error: encryption failed\n");
        }
    } else if (strcmp(argv[1], "-d") == 0) {
        /* Decrypt mode */
        char *decoded = pbDecode(argv[2], &table);
        if (decoded) {
            printf("Decrypted: %s\n", decoded);
            free(decoded);
        } else {
            printf("Error: decryption failed\n");
        }
    } else {
        printf("Invalid option. Use -e to encrypt, -d to decrypt, or -s for batch mode.\n");
        return 1;
    }

    return 0;
}


