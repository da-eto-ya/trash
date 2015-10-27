import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

public class Main {
    public static final int CR = 13;
    public static final int LN = 10;

    public void replaceCRLN(InputStream inputStream, OutputStream outputStream) throws IOException {
        int prev = -1;
        int current;

        while ((current = inputStream.read()) >= 0) {
            if (prev == CR && current != LN) {
                outputStream.write(prev);
            }

            if (current != CR) {
                outputStream.write(current);
            }

            prev = current;
        }

        if (prev == CR) {
            outputStream.write(prev);
        }
    }

    public static void main(String[] args) throws IOException {
        new Main().run();
    }

    private void run() throws IOException {
        replaceCRLN(System.in, System.out);
        System.out.flush();
    }
}