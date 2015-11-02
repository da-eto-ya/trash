import java.util.Comparator;
import java.util.Objects;
import java.util.function.BiConsumer;
import java.util.stream.IntStream;
import java.util.stream.Stream;

public class Streams {
    public static IntStream pseudoRandomStream(int seed) {
        return IntStream.iterate(seed, x -> (x * x / 10) % 1000);
    }

    public static <T> void findMinMax(
            Stream<? extends T> stream,
            Comparator<? super T> order,
            BiConsumer<? super T, ? super T> minMaxConsumer) {
        final T[] m = (T[]) new Object[2];

        stream.forEach(x -> {
            if (m[0] == null || order.compare(x, m[0]) < 0) {
                m[0] = x;
            }

            if (m[1] == null || order.compare(x, m[1]) > 0) {
                m[1] = x;
            }
        });

        minMaxConsumer.accept(m[0], m[1]);
    }

    public static void main(String[] args) {
        IntStream stream = pseudoRandomStream(13);
        stream.limit(8).forEach(x -> System.out.print(x + " "));
        System.out.println();

        findMinMax(
                pseudoRandomStream(13).limit(8).mapToObj(Integer::valueOf),
                Integer::compareTo,
                (Integer x, Integer y) -> System.out.println(x + " =<= " + y)
        );
        System.out.println();
    }
}
