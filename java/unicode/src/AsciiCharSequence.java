public class AsciiCharSequence implements CharSequence {
    private byte[] chars;

    public AsciiCharSequence(byte[] chars) {
        this.chars = new byte[chars.length];
        System.arraycopy(chars, 0, this.chars, 0, chars.length);
    }

    public AsciiCharSequence(byte[] chars, int start, int end) {
        this.chars = new byte[end - start];
        System.arraycopy(chars, start, this.chars, 0, end - start);
    }

    @Override
    public int length() {
        return chars.length;
    }

    @Override
    public char charAt(int index) {
        return (char) chars[index];
    }

    @Override
    public CharSequence subSequence(int start, int end) {
        return new AsciiCharSequence(this.chars, start, end);
    }

    @Override
    public String toString() {
        return new String(chars);
    }

    public static void main(String[] args) {
        byte[] chars = new byte[] {'a', 'b', 'c', 'd', 'e'};
        CharSequence s = new AsciiCharSequence(chars);
        System.out.println(s);
        System.out.println(s.length());
        System.out.println(s.charAt(3));
        System.out.println(s.subSequence(2, 4));
    }
}
