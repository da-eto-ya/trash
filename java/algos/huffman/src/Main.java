import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        new Main().run();
    }

    private void run() {
        Scanner scanner = new Scanner(System.in);
        String s = scanner.nextLine();
        int[] f = new int[26];

        for (char ch : s.toCharArray()) {
            ++f[ch - 'a'];
        }


    }
}
