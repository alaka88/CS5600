/**
 * ProducerThread.java  / Assignment Name
 *
 * ZW / CS5600 / Northeastern University
 * Fall  2025 / Oct 9, 2025
 *
 * Description:
 * This class defines a producer thread that inserts random strings into 
 * a shared BoundedBuffer. Each string is in the format "ThreadID-RandomNumber".
 * The thread inserts a specified number of items into the buffer.
 * 
 */

import java.util.Random;

public class ProducerThread extends Thread {
    private final BoundedBuffer buffer;  // shared buffer object
    private final int threadID;          // identifier for this thread
    private final int numItems;          // number of items to produce
    private final Random rand = new Random();  // random number generator

    // Constructor
    public ProducerThread(BoundedBuffer buffer, int threadID, int numItems) {
        this.buffer = buffer;
        this.threadID = threadID;
        this.numItems = numItems;
    }

    // Run method executed when thread starts
    @Override
    public void run() {
        for (int i = 0; i < numItems; i++) {
            // Generate a 5-digit random number string
            String item = threadID + "-" + String.format("%05d", rand.nextInt(100000));
            try {
                buffer.deposit(item);  // insert item into buffer
                System.out.println("Thread " + threadID + " deposited: " + item);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
