public class Caller {
    public static void main(String[] args) {
        System.out.println(getCallerClassAndMethodName());
        anotherMethod();
    }

    private static void anotherMethod() {
        System.out.println(getCallerClassAndMethodName());
    }

    public static String getCallerClassAndMethodName() {
        StackTraceElement[] stackTraceElements = Thread.currentThread().getStackTrace();

        if (stackTraceElements.length > 3) {
            StackTraceElement lastElem = stackTraceElements[3];
            return lastElem.getClassName() + "#" + lastElem.getMethodName();
        }

        return null;
    }
}
