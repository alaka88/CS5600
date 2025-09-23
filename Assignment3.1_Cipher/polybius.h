/*
* polubius.h / Assignment 3 - Create Cipher
*
* ZW / CS5600 / Northeastern University
* Fall 2025 / Sep 23, 2025
*
* Description:
*   This header file defines the data structure and function prototypes
*   for implementing the Polybius Square cipher.
*   It provides an interface for creating a Polybius table, encoding
*   plaintext into cipher text, and decoding cipher text back into plaintext.
*
*   This file is included in other source files (e.g., polybius.c, cipher.c)
*   so that they can use the cipher functions and table structure.
*
*/
#ifndef POLYBIUS_H
#define POLYBIUS_H

#include <stddef.h>

// Polybius Square size (5x5)
#define SIZE 5

// Table structure
typedef struct {
    char table[SIZE][SIZE];
} polybius_table_t;

/**
 * Initialize the Polybius table.
 * Standard version: A-Z without J (I and J share the same position).
 */
void initTable(polybius_table_t *pt);

/**
 * Encode plaintext into Polybius ciphertext.
 * - Input: plaintext (letters only will be encoded; non-letters are ignored).
 * - Output: malloc'ed string of digits (each letter -> 2 digits).
 * - Caller must free() the result.
 */
char *pbEncode(const char *plaintext, const polybius_table_t *pt);

/**
 * Decode Polybius ciphertext back into uppercase letters.
 * - Input: ciphertext (string of digits '1'..'5'; non-digits ignored).
 * - Output: malloc'ed uppercase string.
 * - Caller must free() the result.
 */
char *pbDecode(const char *ciphertext, const polybius_table_t *pt);

#endif // POLYBIUS_H
