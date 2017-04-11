import java.awt.*;
import java.awt.geom.AffineTransform;
import java.awt.image.AffineTransformOp;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;
import javax.imageio.*;
import javax.imageio.stream.ImageOutputStream;

public class Ulam {
    private final int size;
    private final int dotFactor;
    private final int resizedHeight;

    private Ulam(int size, int dotFactor, int resizedHeight) {
        this.size = size;
        this.dotFactor = dotFactor;
        this.resizedHeight = resizedHeight;
    }

    public static void main(String[] args) throws IOException {
        new Ulam(20000, 1, 1000).run();
    }

    private void log(String msg) {
        System.out.println(msg);
    }

    private void run() throws IOException {
        log("Creating image...");
        BufferedImage img = new BufferedImage(2 * size * dotFactor, 2 * size * dotFactor, BufferedImage.TYPE_BYTE_BINARY);
        Graphics g = img.createGraphics();
        g.setColor(Color.WHITE);
        g.fillRect(0, 0, img.getWidth(), img.getHeight());
        g.setColor(Color.BLACK);

        log("Fill Ulam's square...");
        paint(g);

        log("Saving original...");
        try {
            saveImage(img, new File("ulam.tiff"));
        } catch (IOException e) {
            e.printStackTrace();
        }


        log("All done");
    }

    private void saveImage(BufferedImage image, File file) throws IOException {
        ImageIO.write(image, "TIFF", file);

//        String format = "TIFF";
//        // Get the writer
//        Iterator<ImageWriter> writers = ImageIO.getImageWritersByFormatName(format);
//
//        if (!writers.hasNext()) {
//            throw new IllegalArgumentException("No writer for: " + format);
//        }
//
//        ImageWriter writer = writers.next();
//
//        // Create output stream
//        // Optionally, listen to progress, warnings, etc.
//
//        ImageWriteParam param = writer.getDefaultWriteParam();
//        param.setCompressionMode(ImageWriteParam.MODE_EXPLICIT);
//        param.setCompressionType("PackBits");
////        param.setCompressionQuality(.7f);
//
//
//        // Close stream in finally block to avoid resource leaks
//        ImageOutputStream output = ImageIO.createImageOutputStream(file);
//        writer.setOutput(output);
//
//        writer.write(null, new IIOImage(image, null, null), param);
//
//        output.flush();
//        writer.dispose();
//        output.close();
    }

    private void resizeAndSave(BufferedImage img) throws IOException {
        log("Resize...");
        int h = resizedHeight;
        double ratio = h * 1.0 / img.getHeight();
        int w = (int) (ratio * img.getWidth());
        BufferedImage after = new BufferedImage(w, h, BufferedImage.TYPE_INT_ARGB);
        AffineTransform at = new AffineTransform();
        at.scale(ratio, ratio);
        AffineTransformOp scaleOp = new AffineTransformOp(at, AffineTransformOp.TYPE_BICUBIC);
        after = scaleOp.filter(img, after);

        log("Save resized...");
        ImageIO.write(after, "TIFF", new File("ulam-resized.tiff"));
    }

    private void dot(Graphics g, int x, int y) {
        g.drawRect(x * dotFactor, y * dotFactor, 0, 0);
    }

    private boolean isPrime(ArrayList<Integer> primes, int a) {
        int to = (int) Math.sqrt(a * 1.0);
        boolean undivided = true;

        for (int p : primes) {
            if (p > to) {
                break;
            }

            undivided = a % p > 0;

            if (!undivided) {
                break;
            }
        }

        return undivided;
    }

    private void paint(Graphics g) {
        int current = 1;
        ArrayList<Integer> primes = new ArrayList<Integer>(size * size);
        int[][] dxy = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};

        for (int i = 0; i < size; i++) {
            int n = 2 * i + 1;
            int x = size - 1 - i;
            int y = size + i;

            for (int[] aDxy : dxy) {
                for (int j = 0; j < n; j++) {
                    x += aDxy[0];
                    y += aDxy[1];

                    if (current > 1 && isPrime(primes, current)) {
                        primes.add(current);
                        dot(g, x, y);
                    }

                    current++;
                }
            }

            log(String.format("Radius: %4d\t Next: %4d\t Primes: %4d", i + 1, current, primes.size()));
        }
    }
}
