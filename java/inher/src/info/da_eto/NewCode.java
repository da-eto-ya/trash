package info.da_eto;

import java.util.*;

public class NewCode {
    /**
     * Интерфейс -- для красоты и определённости, можно и без него.
     */
    interface IAmAClass {
        Collection<Integer> getStorage();
    }

    static abstract class A implements IAmAClass {
        protected final Collection<Integer> a = new LinkedList<>();

        /**
         * Геттер для a (можно сделать имя покороче).
         * @return
         */
        @Override
        public Collection<Integer> getStorage() {
            return a;
        }

        /**
         * Здесь (и везде дальше) используется getStorage().
         */
        public void prepareData() {
            for (int i = 0; i < 10; ++i) {
                getStorage().add(i);
            }
        }
    }

    /**
     * Класс, который имплементирует своё хранилище.
     */
    static class B extends A implements IAmAClass {
        /**
         * Мы всё ещё не можем переопределять данные, поэтому совпадение имён здесь -- просто совпадение.
         */
        protected final Collection<Integer> a = new ArrayList<>();

        /**
         * Поскольку мы хотим использовать новое хранилище, то нам нужно переопределить этот метод, да.
         * @return
         */
        @Override
        public Collection<Integer> getStorage() {
            return a;
        }

        public void run() {
            System.out.println(a.isEmpty());
        }
    }

    /**
     * Класс, которому не нужно менять хранилище (используется то, которое было в A).
     */
    static class С extends A implements IAmAClass {
        public void run() {
            System.out.println(a.isEmpty());
        }
    }

    public static void main(String[] args) {
        B b = new B();
        b.prepareData();
        b.run();

        С с = new С();
        с.prepareData();
        с.run();
    }
}
