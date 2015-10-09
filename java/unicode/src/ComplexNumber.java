public final class ComplexNumber {
    private final double re;
    private final double im;

    public ComplexNumber(double re, double im) {
        this.re = re;
        this.im = im;
    }

    public double getRe() {
        return re;
    }

    public double getIm() {
        return im;
    }

    @Override
    public boolean equals(Object obj) {
        return this == obj || obj instanceof ComplexNumber &&
                re == ((ComplexNumber) obj).getRe() &&
                im == ((ComplexNumber) obj).getIm();
    }

    @Override
    public int hashCode() {
        long reHash = Double.doubleToLongBits(re);
        long imHash = Double.doubleToLongBits(im);

        return (int) ((reHash * 31 + imHash) % Integer.MAX_VALUE);
    }

    public static void main(String[] args) {
        ComplexNumber a = new ComplexNumber(1, 1);
        ComplexNumber b = new ComplexNumber(1, 1);
        System.out.println(a.equals(b));
        System.out.println(a.hashCode() == b.hashCode());
    }
}
