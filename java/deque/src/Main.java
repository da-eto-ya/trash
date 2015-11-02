import java.io.BufferedInputStream;
import java.util.ArrayDeque;
import java.util.Deque;
import java.util.Iterator;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner in = new Scanner(new BufferedInputStream(System.in));
        Deque<Integer> deque = new ArrayDeque<>();
        boolean even = false;

        while (in.hasNext()) {
            int e = in.nextInt();

            if (even) {
                deque.addLast(e);
            }

            even = !even;
        }

        Iterator<Integer> it = deque.descendingIterator();

        while (it.hasNext()) {
            System.out.print(it.next());
            System.out.print(" ");
        }
    }
}
