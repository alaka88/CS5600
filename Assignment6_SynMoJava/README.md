# Assignment 6 - Synchronization with Monitors (Java)

## Author
ZW

## Description
This project implements a multi-threaded Bounded Buffer using Java Locks and Condition variables, following the tutorial by Baptiste Wicht on Java Concurrency - Part 5: Monitors (Locks and Conditions).  

The program includes:
- `BoundedBuffer.java`: Implementation of a bounded buffer using ReentrantLock and Condition variables.
- `ProducerThread.java`: Multi-threaded producer class that inserts 5-digit random number strings into the buffer.
- `Main.java`: Main program to start multiple producer threads and store data in the bounded buffer.

The project demonstrates:
- Thread-safe access to shared resources
- Mutual exclusion using locks
- Waiting and signaling threads using Condition variables
- Multi-threaded programming in Java

---

## How to Compile and Run

1. Compile all Java files using Make:
This will clean previous .class files and compile all .java files
```bash
make

2.Run the program:
The program will start multiple producer threads and insert 5-digit random number strings into the bounded buffer.
```bash
make run

3.To remove all compiled .class files:
```bash
make clean
