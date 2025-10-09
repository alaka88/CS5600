/**
 * Main.java / Assignment Name
*
* ZW / CS5600 / Northeastern University
* Fall 2025 / Oct 9, 2025
* 
 * Description:
 * This is the main program for Assignment 6. It creates a shared BoundedBuffer,
 * starts multiple ProducerThread instances to insert random strings into the buffer,
 * and waits for all threads to complete. Each thread produces a fixed number of items。
 */

public class Main {
    public static void main(String[] args) throws InterruptedException {
        int bufferCapacity = 100;   // capacity of the bounded buffer
        int numThreads = 3;        // number of producer threads
        int itemsPerThread = 30;   // number of items each thread will produce

        BoundedBuffer buffer = new BoundedBuffer(bufferCapacity);

        ProducerThread[] producers = new ProducerThread[numThreads];

        // Create and start producer threads
        for (int i = 0; i < numThreads; i++) {
            producers[i] = new ProducerThread(buffer, i + 1, itemsPerThread);
            producers[i].start();
        }

        // Wait for all threads to finish
        for (ProducerThread producer : producers) {
            producer.join();
        }

        System.out.println("All threads finished producing.");
    }
}
