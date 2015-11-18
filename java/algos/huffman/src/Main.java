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

        public Node getLeft() {
            return left;
        }

        public Node getRight() {
            return right;
        }

        public char getLabel() {
            return label;
        }

        public void print() {
            print("", true);
        }

        private void print(String prefix, boolean isTail) {
            System.out.println(prefix + (isTail ? "└── " : "├── ") + frequency + (label != 0 ? " (" + label + ")" : ""));

            if (left != null) {
                left.print(prefix + (isTail ? "    " : "│   "), false);
            }

            if (right != null) {
                right.print(prefix + (isTail ?"    " : "│   "), true);
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
        result.print();
    }
}
