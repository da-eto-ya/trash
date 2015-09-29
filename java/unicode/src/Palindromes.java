public class Palindromes {
    public static void main(String[] args) {
        System.out.println(isPalindrome("a1234*#@#@567^*&$#89(*0)_*09#%^(8765(&%$4321)&^$#A"));
    }

    public static boolean isPalindrome(String text) {
        String s = text.toLowerCase()
                .chars().filter(Character::isLetterOrDigit)
                .mapToObj(i -> Character.toString((char) i)).reduce("", String::concat);
        return s.equals(new StringBuilder(s).reverse().toString());
    }
}
