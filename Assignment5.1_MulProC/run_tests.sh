#!/bin/bash
# run_tests.sh - Automated test script for Assignment 5
# ZW / CS5600 / Northeastern University
# Fall 2025 / Sep 30, 2025
#
# Description:
#   This script runs multiple test cases against mainAssign5 and cipher,
#   checking normal and edge cases. Results are logged in test_results.log.

PROG=./main
CIPHER=./cipher
LOG=test_results.log

echo "=== Assignment 5 Test Results ===" > $LOG
date >> $LOG
echo "" >> $LOG

# Test Case 1: Normal input file
echo "[Test 1] Normal file with 250 words" | tee -a $LOG
./genRandWords-wang 250 words.txt
$PROG words.txt >> $LOG 2>&1
ls output_*.txt >> $LOG 2>&1
echo "" >> $LOG

# Test Case 2: Empty input file
echo "[Test 2] Empty file" | tee -a $LOG
touch empty.txt
$PROG empty.txt >> $LOG 2>&1
echo "" >> $LOG

# Test Case 3: File without sentence terminators
echo "[Test 3] No sentence terminators" | tee -a $LOG
echo "this is a test file without punctuation markers at all" > nosentence.txt
$PROG nosentence.txt >> $LOG 2>&1
echo "" >> $LOG

# Test Case 4: Cipher program missing
echo "[Test 4] Cipher missing" | tee -a $LOG
mv $CIPHER cipher_backup   # temporarily hide cipher
$PROG words.txt >> $LOG 2>&1
mv cipher_backup $CIPHER   # restore
echo "" >> $LOG

# Test Case 5: Very long word
echo "[Test 5] Very long word" | tee -a $LOG
echo "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz" > longword.txt
$PROG longword.txt >> $LOG 2>&1
echo "" >> $LOG

# Test Case 6: Large file stress test
echo "[Test 6] Large file (10000 words)" | tee -a $LOG
./genRandWords-wang 10000 big.txt
$PROG big.txt >> $LOG 2>&1
ls output_*.txt | head -10 >> $LOG 2>&1   # list first 10 outputs for sanity
echo "" >> $LOG

# Test Case 7: Invalid usage
echo "[Test 7] Invalid usage (no arguments)" | tee -a $LOG
$PROG >> $LOG 2>&1
echo "" >> $LOG

echo "=== Tests Complete ===" | tee -a $LOG
echo "Results saved to $LOG"
