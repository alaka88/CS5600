Assignment 3 - Polybius Cipher
ZW - CS5600 - Operating Systems

Description:
Implementation of the Polybius Square cipher in C with encryption and decryption.

Files:
- polybius.h / polybius.c : Cipher functions
- cipher.c                : Main program
- Makefile                : Build instructions

Compile:
make

Usage:
./cipher -e "text"    # Encrypt
./cipher -d "digits"  # Decrypt

Example:
./cipher -e "hello world"
Encrypted: 23153131345234423114

./cipher -d "23153131345234423114"
Decrypted: HELLOWORLD

