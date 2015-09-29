public class Main {
    public char charExpression(int a) {
        return (char) ('\\' + a);
    }

    public static void main(String[] args) {
        System.out.println(new Main().charExpression(32));
    }

    public Main() {
    }
}
