package concurrency.semaphore.java;

import java.util.concurrent.Semaphore;

public class SemaphoreTests {
    static Semaphore sem = new Semaphore(0);

    public static void main(String[] args) throws InterruptedException {

        Thread t = new Thread(() -> {
            System.out.println("child");
            sem.release();
        });

        t.start();

        System.out.println("parent: begin");
        sem.acquire();
        System.out.println("parent: end");
    }
}
