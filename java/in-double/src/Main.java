import java.io.InputStream;
import java.util.Locale;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        new Main().run();
    }

    public double sumInput(InputStream inputStream) {
        double sum = .0;
        Scanner scanner = new Scanner(inputStream);

        while (scanner.hasNext()) {
            try {
                sum += Double.parseDouble(scanner.next());
            } catch (NumberFormatException ignored) {
            }
        }

        return sum;
    }

    private void run() {
        double sum = sumInput(System.in);
        System.out.printf(Locale.US, "%.6f\n", sum);
    }
}