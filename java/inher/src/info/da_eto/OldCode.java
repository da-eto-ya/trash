package info.da_eto;

import java.util.*;

public class OldCode {
    /**
     * Статик-классы -- чтобы больше были похожи на классы из других файлов без использования других файлов.
     */
    static abstract class A {
        protected final Collection<Integer> a = new LinkedList<>();

        public void prepareData() {
            for (int i = 0; i < 10; ++i) {
                a.add(i);
            }
        }
    }

    static class B extends A {
        protected final Collection<Integer> a = new ArrayList<>();

        /**
         * Для демонстрации достаточно run(), next() лень писать.
         */
        public void run() {
            System.out.println(a.isEmpty());
        }
    }

    public static void main(String[] args) {
        B b = new B();
        b.prepareData();
        b.run();
    }
}
