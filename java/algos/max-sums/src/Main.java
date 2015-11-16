import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        long n = scanner.nextLong();
        long k = 1;

        while (k * (k + 1L) <= 2 * n) {
            ++k;
        }

        --k;

        System.out.println(k);

        for (long i = 1; i < k; i++) {
            System.out.print(i);
            System.out.print(" ");
        }

        long r = n - (k * (k - 1)) / 2;
        System.out.println(r);
    }
}
