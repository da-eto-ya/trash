import java.io.UnsupportedEncodingException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

/**
 * MD5 calculator.
 */
public class Main {
    /**
     * Entry point.
     *
     * @param args command line arguments
     */
    public static void main(String[] args) throws NoSuchAlgorithmException, UnsupportedEncodingException {
        if (args.length != 1) {
            System.exit(-1);
        }

        MessageDigest md = MessageDigest.getInstance("MD5");
        byte[] digest = md.digest(args[0].getBytes("UTF-8"));

        for (byte b : digest) {
            System.out.printf("%02x", b);
        }
    }
}
