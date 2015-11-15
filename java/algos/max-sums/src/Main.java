import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        long n = scanner.nextLong();
        long k = (long) Math.floor(Math.sqrt(1L + 4L * n) / 2.0);

        if ((k + 1L) * (k + 2L) == 2 * n) {
            k = k + 1;
        }

        long r = k * (k + 1L) / 2;

        System.out.println(k);

        for (long i = 1L; i < k; i++) {
            System.out.print(i);
            System.out.print(" ");
        }

        System.out.print(k + (n - r));
    }
}
