/*
* polybius.c / Assignment 3 - Create Cipher
*
* ZW / CS5600 / Northeastern University
* Fall 2025 / Sep 23, 2025
* Description:
*   Implementation of the Polybius Square cipher functions.
*   Provides functions to initialize a Polybius table, encode plaintext
*   into numeric ciphertext, and decode ciphertext back into plaintext.
*   Letters I and J share the same cell in the 5x5 grid.
*
*   This file implements the interface defined in polybius.h and is
*   intended to be used by other programs (e.g., cipher.c) to perform
*   encryption and decryption.
*
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "polybius.h"

/**
 * Initialize the Polybius square (5x5).
 * Uses letters A–Z but merges I and J into the same cell.
 */
void initTable(polybius_table_t *pt) {
    const char *alphabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ"; /* 25 letters, no J */
    int k = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            pt->table[i][j] = alphabet[k++];
        }
    }
}

/**
 * Find the position of a character inside the Polybius square.
 * Converts J into I because they share the same cell.
 */
static void findChar(const polybius_table_t *pt, char c, int *row, int *col) {
    if (c == 'J') c = 'I';  /* merge I and J */
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (pt->table[i][j] == c) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

/**
 * Encrypt plaintext into Polybius cipher text.
 * Only alphabetic characters are encoded; other characters are ignored.
 * Each letter is represented by two digits (row and column).
 * Returns a dynamically allocated string that must be freed by the caller.
 */
char *pbEncode(const char *plaintext, const polybius_table_t *pt) {
    size_t len = strlen(plaintext);
    char *ciphertext = malloc(len * 2 + 1);  /* two digits per letter */
    if (!ciphertext) return NULL;

    int pos = 0;
    for (size_t i = 0; i < len; i++) {
        if (isalpha((unsigned char)plaintext[i])) {
            char c = toupper((unsigned char)plaintext[i]);
            int row, col;
            findChar(pt, c, &row, &col);
            ciphertext[pos++] = '1' + row;  /* row number (1–5) */
            ciphertext[pos++] = '1' + col;  /* column number (1–5) */
        }
    }
    ciphertext[pos] = '\0';
    return ciphertext;
}

/**
 * Decrypt Polybius cipher text back into plaintext.
 * The cipher text must consist of digit pairs (row and column).
 * Returns a dynamically allocated string that must be freed by the caller.
 */
char *pbDecode(const char *ciphertext, const polybius_table_t *pt) {
    size_t len = strlen(ciphertext);
    char *plaintext = malloc(len / 2 + 1);  /* one letter per two digits */
    if (!plaintext) return NULL;

    int pos = 0;
    for (size_t i = 0; i < len; i += 2) {
        int row = ciphertext[i] - '1';
        int col = ciphertext[i + 1] - '1';
        if (row >= 0 && row < SIZE && col >= 0 && col < SIZE) {
            plaintext[pos++] = pt->table[row][col];
        }
    }
    plaintext[pos] = '\0';
    return plaintext;
}
