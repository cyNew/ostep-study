import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class ProducerConsumer {
    static final int MAX_SIZE = 10;
    static final Lock lock = new ReentrantLock();
    static Condition EPMTY = lock.newCondition();
    static Condition FILL = lock.newCondition();
    static List<Integer> list = new ArrayList<>(MAX_SIZE);

    static class Producer implements Runnable {
        final int loops;

        public Producer(int loops) {
            this.loops = loops;
        }

        @Override
        public void run() {
            for (int i = 0; i < loops; i++) {
                lock.lock();
                try {
                    while (list.size() == MAX_SIZE) {
                        EPMTY.await();
                    }
                    list.addLast(i);
                    FILL.signalAll();
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                } finally {
                    lock.unlock();
                }
            }
        }
    }

    static class Consumer implements Runnable {
        @Override
        public void run() {
            while (true) {
                lock.lock();
                try {
                    while (list.size() == 0) {
                        FILL.await();
                    }

                    int tmp = list.removeFirst();
                    EPMTY.signalAll();
                    System.out.printf("%s consume: %d\n", Thread.currentThread().getName(), tmp);
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                } finally {
                    lock.unlock();
                }
            }
        }
    }

    public static void main(String[] args) throws InterruptedException {
        var producer = new Thread(new Producer(100), "Producer");
        var consumer1 = new Thread(new Consumer(), "Consmer-1");
        var consumer2 = new Thread(new Consumer(), "Consumer-2");

        producer.start();
        consumer1.start();
        consumer2.start();
        TimeUnit.SECONDS.sleep(5);
    }
}
