import java.util.stream.IntStream;

public class Streams {
    public static IntStream pseudoRandomStream(int seed) {
        return IntStream.iterate(seed, x -> (x * x / 10) % 1000);
    }

    public static void main(String[] args) {
        IntStream stream = pseudoRandomStream(13);
        stream.limit(10).forEach(x -> System.out.println(x));
    }
}
