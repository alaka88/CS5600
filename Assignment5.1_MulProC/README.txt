# Assignment 5 – Multiprocessing in C

## Files Included
- `Makefile`
- `main.c`
- `queue.c`, `queue.h`
- `cipher.c`
- `polybius.c`, `polybius.h`
- `genRandWords-wang.c`
- `run_tests.sh`

## Compilation and Execution

### Compile All Programs
Simply run:
```bash
make
----
This generates the following executables:
main
cipher
genRandWords-wang

###Run Automated Tests
Simply run:
```bash
make test
---
This executes the automated test script run_tests.sh, which:
Generates test word files for various edge cases:
words.txt with 250 words (normal file)
empty.txt (empty file)
nosentence.txt (no sentence terminators)
longword.txt (very long word)
big.txt with 10,000 words
Produces output files for each batch of 100 words:
output_1.txt, output_2.txt, ..., approximately 100 files for big.txt
Saves test results to test_results.log

###Clean Up
Simply run:
```bash
make clean
---
Removes all compiled executables and temporary files (output_*.txt).

