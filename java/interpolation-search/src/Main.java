import java.math.BigDecimal;
import java.math.BigInteger;
import java.util.Arrays;
import java.util.Random;

public class Main {
    private static final int CHUNK_POW = 18;
    private static final int RANDOM_SAMPLES = 7;

    public static void main(String[] args) {
        new Main().run();
    }

    private int interpolationSearch(final BigInteger[] a, final int fromIndex, final int toIndex, final BigInteger key) {
        checkBounds(a, fromIndex, toIndex);

        int low = fromIndex;
        int high = toIndex - 1;

        while (low <= high) {
            if (a[high].equals(a[low])) {
                if (a[low].equals(key)) {
                    return low;
                } else {
                    return -1;
                }
            }

            BigDecimal p = new BigDecimal(key.subtract(a[low]));
            BigDecimal q = new BigDecimal(a[high].subtract(a[low]));
            double quotient = p.divide(q, 12, BigDecimal.ROUND_FLOOR).doubleValue();
            int mid = low + (int) ((high - low) * quotient);

            // fallback
            if (mid > high) {
                mid = (low + high) >>> 1;
            }

            BigInteger midVal = a[mid];
            int cmp = midVal.compareTo(key);

            if (cmp < 0) {
                low = mid + 1;
            } else if (cmp > 0) {
                high = mid - 1;
            } else {
                return mid; // key found
            }
        }

        return -1;  // key not found.
    }

    private void checkBounds(BigInteger[] a, int fromIndex, int toIndex) {
        if (fromIndex > toIndex) {
            throw new IllegalArgumentException("fromIndex(" + fromIndex + ") > toIndex(" + toIndex + ")");
        }

        if (fromIndex < 0) {
            throw new ArrayIndexOutOfBoundsException(fromIndex);
        }

        if (toIndex > a.length) {
            throw new ArrayIndexOutOfBoundsException(toIndex);
        }
    }

    private void run() {
        Random random = new Random();
        int size = 1 << CHUNK_POW;
        // FIXME: remove
        System.out.println(size);

        BigInteger[][] lists = new BigInteger[4][size];
        generateFibonacciList(lists[0]);
        generatePowers2List(lists[1]);
        generateUniformList(lists[2], 7, random);
        generateUniformList(lists[3], 255, random);

        int samplesSize = 3 + RANDOM_SAMPLES;
        BigInteger[] samples = new BigInteger[samplesSize];
        long[][] durations = new long[2][samplesSize];

        for (int from = 0, to = 1; to < size; to = to << 1) {
            System.out.println("Size: " + to);

            for (int l = 0; l < lists.length; l++) {
                BigInteger[] list = lists[l];
                System.out.println("List: " + l);

                // prepare samples
                samples[0] = list[from];
                samples[1] = list[to - 1];
                samples[2] = list[to / 2];

                for (int i = 0; i < RANDOM_SAMPLES; i++) {
                    samples[3 + i] = list[random.nextInt(to)];
                }

                for (int i = 0; i < samples.length; i++) {
                    BigInteger sample = samples[i];
                    long start;

                    start = System.nanoTime();
                    int binarySearchResult = Arrays.binarySearch(list, from, to, sample, null);
                    durations[0][i] = System.nanoTime() - start;

                    start = System.nanoTime();
                    int interpolationSearchResult = interpolationSearch(list, from, to, sample);
                    durations[1][i] = System.nanoTime() - start;

                    if (!list[binarySearchResult].equals(list[interpolationSearchResult])) {
                        System.out.printf("ERROR: BS(%d) <> IS(%d)\n", binarySearchResult, interpolationSearchResult);
                        return;
                    }
                }

//                System.out.println("Samples:\t");
//                for (BigInteger sample : samples) {
//                    System.out.print(sample);
//                    System.out.print("\t");
//                }
//                System.out.println();
//
//                System.out.println("BS:\t");
                for (long duration : durations[0]) {
                    System.out.printf("%d\t", duration);
                }
                System.out.println();

//                System.out.println("IS:\t");
                for (long duration : durations[1]) {
                    System.out.printf("%d\t", duration);
                }
                System.out.println();
            }

            System.out.println();
        }
    }

    private void generateFibonacciList(BigInteger[] list) {
        list[0] = BigInteger.ONE;
        list[1] = BigInteger.ONE;

        for (int i = 2; i < list.length; i++) {
            list[i] = list[i - 1].add(list[i - 2]);
        }
    }

    private void generatePowers2List(BigInteger[] list) {
        BigInteger two = new BigInteger("2");
        list[0] = BigInteger.ONE;

        for (int i = 1; i < list.length; i++) {
            list[i] = list[i - 1].multiply(two);
        }
    }

    private void generateUniformList(BigInteger[] list, int numBits, Random random) {
        for (int i = 0; i < list.length; i++) {
            list[i] = new BigInteger(numBits, random);
        }

        Arrays.sort(list);
    }
}
