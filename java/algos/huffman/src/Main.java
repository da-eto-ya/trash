import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        new Main().run();
    }

    public static class Node {
        private char label;
        private int frequency;
        private Node left;
        private Node right;
        private String code;

        public Node(char label, int frequency) {
            this.label = label;
            this.frequency = frequency;
        }

        public Node(int frequency, Node left, Node right) {
            this.frequency = frequency;
            this.left = left;
            this.right = right;
        }

        public int getFrequency() {
            return frequency;
        }

        public char getLabel() {
            return label;
        }

        // TODO: merge buildCodes and getCodes
        public void buildCodes(String prefix) {
            if (label != 0) {
                code = prefix;
            } else {
                left.buildCodes(prefix + "0");
                right.buildCodes(prefix + "1");
            }
        }

        public String[] getCodes() {
            String[] codes = new String[26];
            fillCode(codes);
            return codes;
        }

        private void fillCode(String[] codes) {
            if (label != 0) {
                codes[label - 'a'] = code;
            } else {
                left.fillCode(codes);
                right.fillCode(codes);
            }
        }
    }

    private void run() {
        Scanner scanner = new Scanner(System.in);
        String s = scanner.nextLine();
        int[] f = new int[26];

        for (char ch : s.toCharArray()) {
            ++f[ch - 'a'];
        }

        PriorityQueue<Node> queue = new PriorityQueue<>(26, Comparator.comparing(Node::getFrequency));

        for (int i = 0; i < f.length; i++) {
            if (f[i] > 0) {
                queue.add(new Node((char) ('a' + i), f[i]));
            }
        }

        while (queue.size() > 1) {
            Node a = queue.poll();
            Node b = queue.poll();
            Node n = new Node(a.getFrequency() + b.getFrequency(), a, b);
            queue.add(n);
        }

        Node result = queue.poll();

        // FIXME: bad code, bad!
        if (result.getLabel() != 0) {
            result.buildCodes("0");
        } else {
            result.buildCodes("");
        }

        String[] codes = result.getCodes();
        int k = 0;

        for (int i = 0; i < codes.length; i++) {
            if (codes[i] != null) {
                ++k;
            }
        }

        StringBuilder sb = new StringBuilder(s.length() * 10);

        for (char ch : s.toCharArray()) {
            sb.append(codes[ch - 'a']);
        }

        String r = sb.toString();

        System.out.print(k);
        System.out.print(" ");
        System.out.println(r.length());

        for (int i = 0; i < codes.length; i++) {
            if (codes[i] != null) {
                System.out.print((char) ('a' + i));
                System.out.print(": ");
                System.out.println(codes[i]);
            }
        }

        System.out.println(r);
    }
}
