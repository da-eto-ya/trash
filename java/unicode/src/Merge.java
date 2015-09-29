import java.util.Arrays;

public class Merge {
    public static void main(String[] args) {
        int[] a1 = {0, 2};
        int[] a2 = {1, 3};
        System.out.println(Arrays.toString(mergeArrays(a1, a2)));
    }

    private static int[] mergeArrays(int[] a1, int[] a2) {
        int[] res = new int[a1.length + a2.length];

        for (int p1 = 0, p2 = 0, pRes = 0; p1 < a1.length || p2 < a2.length; ++pRes) {
            if (p1 < a1.length && p2 < a2.length) {
                if (a1[p1] < a2[p2]) {
                    res[pRes] = a1[p1++];
                } else {
                    res[pRes] = a2[p2++];
                }
            } else if (p1 < a1.length) {
                res[pRes] = a1[p1++];
            } else {
                res[pRes] = a2[p2++];
            }
        }

        return res;
    }
}
