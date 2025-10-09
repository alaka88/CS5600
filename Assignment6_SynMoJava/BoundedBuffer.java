/**
 * BoundedBuffer.java / Synchronization with Monitors
 *
 * ZW / CS5600 / Northeastern University
 * Fall 2025 / Oct 9, 2025
 * 
 * Description:
 * This class implements a thread-safe bounded buffer using Java's 
 * ReentrantLock and Condition variables. It supports multiple producer 
 * and consumer threads safely.
 * 
 * Reference:
 * Bounded Buffer example from Baptiste Wicht, "Java Concurrency - Part 5: Monitors"
 */

import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class BoundedBuffer {
    private final String[] buffer;  // buffer array to store data
    private final int capacity;     // maximum capacity of the buffer
    private int front = 0;          // index for next fetch
    private int rear = 0;           // index for next deposit
    private int count = 0;          // number of items currently in buffer

    private final Lock lock = new ReentrantLock();       // lock for mutual exclusion
    private final Condition notFull = lock.newCondition();  // condition for buffer not full
    private final Condition notEmpty = lock.newCondition(); // condition for buffer not empty

    // Constructor
    public BoundedBuffer(int capacity) {
        this.capacity = capacity;
        this.buffer = new String[capacity];
    }

    // Deposit data into buffer (producer)
    public void deposit(String data) throws InterruptedException {
        lock.lock();
        try {
            while (count == capacity) {       // buffer full, wait
                notFull.await();
            }
            buffer[rear] = data;              // insert data
            rear = (rear + 1) % capacity;     // circular buffer
            count++;
            notEmpty.signal();                // signal that buffer is not empty
        } finally {
            lock.unlock();
        }
    }

    // Fetch data from buffer (consumer)
    public String fetch() throws InterruptedException {
        lock.lock();
        try {
            while (count == 0) {              // buffer empty, wait
                notEmpty.await();
            }
            String result = buffer[front];    // retrieve data
            front = (front + 1) % capacity;   // circular buffer
            count--;
            notFull.signal();                 // signal that buffer is not full
            return result;
        } finally {
            lock.unlock();
        }
    }
}
