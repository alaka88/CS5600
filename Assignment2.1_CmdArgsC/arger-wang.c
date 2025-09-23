/*
 * arger-wang.c / Assignment2 - Command Line Arguments
 *
 * ZW / CS5600 / Northeastern University
 * Fall 2025 / Sep 16, 2025
 *
 * Description:
 *   This program accepts command-line arguments and processes text
 *   according to the given option:
 *      -u   convert to uppercase
 *      -l   convert to lowercase
 *      -cap capitalize each word
 *   If the option is invalid, the program prints an error message
 *   and exits with error code -1.
 */
#include <stdio.h>

int main(int argc, char *argv[]) {
    // Check if there are enough arguments.
    if (argc < 3) {
        printf("Error: Not enough arguments.\n");// Inform the user
        return -1;// Exit with error code -1 
    }
    
    // The first argument is the option (-u, -l, -cap)
    char *option = argv[1];

    // Check if the first argument starts with '-' as required
    if (option[0] != '-') {
        printf("Error: First argument must start with '-'.\n");
        return -1;
    }

    // Loop through each word provided after the option
    for (int i = 2; i < argc; i++) {
        char *word = argv[i]; // Get the current word
        for (int j = 0; word[j] != '\0'; j++) {  // Loop through each character in the word
            char c = word[j];   // Current character
 
            // Check the option and process accordingly
            if (option[1] == 'u' && option[2] == '\0') {
                // Option -u: convert all letters to uppercase
                if (c >= 'a' && c <= 'z') c -= 32; // ASCII: 'a' - 'A' = 32
            } 
            else if (option[1] == 'l' && option[2] == '\0') {
                // Option -l: convert all letters to lowercase
                if (c >= 'A' && c <= 'Z') c += 32;
            } 
            else if (option[1] == 'c' && option[2] == 'a' && option[3] == 'p' && option[4] == '\0') {
                // Option -cap: capitalize first letter of each word
                if (j == 0 && c >= 'a' && c <= 'z') c -= 32; // First letter uppercase
                else if (j != 0 && c >= 'A' && c <= 'Z') c += 32; // Other letters lowercase
            } 
            else {
                // If option does not match any valid one, print error and exit
                printf("Error: Unknown option.\n");
                return -1;
            }

            printf("%c", c); // Print processed character
        }
        printf(" "); // Print a space between words
    }

    printf("\n"); // End with a newline
    return 0; // Exit successfully
}
