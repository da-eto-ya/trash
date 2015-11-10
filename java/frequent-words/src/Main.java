import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.Comparator;
import java.util.Map;
import java.util.function.Function;
import java.util.stream.Collectors;

public class Main {
    public static void main(String[] args) {
        new BufferedReader(new InputStreamReader(System.in)).lines()
                .map(s -> s.split("[^\\p{L}\\p{Mn}\\p{Nd}]+")).flatMap(Arrays::stream)
                .map(String::toLowerCase)
                .collect(Collectors.groupingBy(Function.<String>identity())).entrySet().stream()
                .collect(Collectors.toMap(Map.Entry::getKey, e -> e.getValue().size())).entrySet().stream()
                .sorted(Map.Entry.<String, Integer>comparingByValue(Comparator.<Integer>reverseOrder())
                                .thenComparing(Map.Entry.<String, Integer>comparingByKey())
                )
                .map(Map.Entry::getKey)
                .limit(10)
                .forEach(System.out::println);
    }
}
