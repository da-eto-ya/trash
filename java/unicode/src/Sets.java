import java.util.*;

public class Sets {
    public static <T> Set<T> symmetricDifference(Set<? extends T> set1, Set<? extends T> set2) {
        Set<T> set = new HashSet<>(set1);
        set.addAll(set2);
        Set<T> intersection = new HashSet<>(set1);
        intersection.retainAll(set2);
        set.removeAll(intersection);

        return set;
    }

    public static void main(String[] args) {
        Set<Integer> s1 = new HashSet<>();
        Collections.addAll(s1, 1, 2, 3);
        Set<Integer> s2 = new HashSet<>();
        Collections.addAll(s2, 0, 1, 2);
        Set<Integer> sXor = symmetricDifference(s1, s2);

        for (Integer i : sXor) {
            System.out.println(i);
        }
    }
}
