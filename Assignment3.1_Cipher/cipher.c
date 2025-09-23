/*
* cipher.c / Assignment 3 - Program in C
*
* ZW / CS5600 / Northeastern University
* Fall 2025 / Sep 23, 2025
*
* Description:
*   This is the main program for the Polybius cipher assignment.
*   It uses the Polybius square defined in polybius.h / polybius.c
*   to perform encryption and decryption of text from the command line.
*
*   Usage examples:
*     ./cipher -e "this is plain text"   --> encrypts plaintext
*     ./cipher -d "ciphertext"           --> decrypts ciphertext
*
*   The program initializes a Polybius table (5x5) and then
*   calls pbEncode() or pbDecode() depending on the command-line option.
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "polybius.h"

/**
 * Main program for the Polybius cipher.
 * Description:
 *   This is the main program for the Polybius cipher assignment.
 *   It uses the Polybius square defined in polybius.h / polybius.c
 *   to perform encryption and decryption of text from the command line.
 *
 * Usage:
 *   ./cipher -e "your message here"   --> encrypt
 *   ./cipher -d "ciphertext"          --> decrypt
 *
 *   The program initializes a Polybius table (5x5) and then
 *   calls pbEncode() or pbDecode() depending on the command-line option.
 */
int main(int argc, char *argv[]) {
    polybius_table_t table;
    initTable(&table);  /* create Polybius square */

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
        printf("Invalid option. Use -e to encrypt or -d to decrypt.\n");
        return 1;
    }

    return 0;
}

