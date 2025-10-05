# Assignment 5 – Multithreading in C

## Files Included
- `Makefile`
- `main.c`
- `queue.c`, `queue.h`
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
genRandWords-wang

###Run Automated Tests
Simply run:
```bash
make test
---
Generates test word files for various cases:
words.txt – 250 words (normal file)
empty.txt – empty file
nosentence.txt – file without sentence terminators
longword.txt – file with a very long word
big.txt – 10,000 words for stress testing
Runs the multithreaded main program on each test file.
Produces output files for each batch of 100 words:
output_1.txt, output_2.txt, etc.
Saves test results and logs to test_results.log.

###Clean Up
Simply run:
```bash
make clean
---
Removes all compiled executables and temporary files (output_*.txt).

