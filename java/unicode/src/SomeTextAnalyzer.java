public class SomeTextAnalyzer {
    interface TextAnalyzer {
        Label processText(String text);
    }

    enum Label {
        SPAM, NEGATIVE_TEXT, TOO_LONG, OK
    }

    public static void main(String[] args) {
        new SomeTextAnalyzer().run();
    }

    private void run() {
        TextAnalyzer[] analyzers = new TextAnalyzer[]{
                new SpamAnalyzer(new String[]{"bad", "words"}),
                new NegativeTextAnalyzer(),
                new TooLongTextAnalyzer(30),
        };
        System.out.println(checkLabels(analyzers, "hello"));
        System.out.println(checkLabels(analyzers, "some words are not good"));
        System.out.println(checkLabels(analyzers, "or have :( mood"));
        System.out.println(checkLabels(analyzers, "or are too long for this very short life and very short read"));
    }

    abstract class KeywordAnalyzer implements TextAnalyzer {
        abstract protected String[] getKeywords();

        abstract protected Label getLabel();

        @Override
        public Label processText(String text) {
            for (String keyword : getKeywords()) {
                if (text.contains(keyword)) {
                    return getLabel();
                }
            }

            return Label.OK;
        }
    }

    class SpamAnalyzer extends KeywordAnalyzer implements TextAnalyzer {
        private final String[] keywords;

        public SpamAnalyzer(String[] keywords) {
            this.keywords = keywords.clone();
        }

        @Override
        protected String[] getKeywords() {
            return keywords;
        }

        @Override
        protected Label getLabel() {
            return Label.SPAM;
        }
    }

    class NegativeTextAnalyzer extends KeywordAnalyzer implements TextAnalyzer {
        private final String[] keywords = {":(", "=(", ":|"};

        @Override
        protected String[] getKeywords() {
            return keywords;
        }

        @Override
        protected Label getLabel() {
            return Label.NEGATIVE_TEXT;
        }
    }

    class TooLongTextAnalyzer implements TextAnalyzer {
        private final int maxLength;

        public TooLongTextAnalyzer(int maxLength) {
            this.maxLength = maxLength;
        }

        @Override
        public Label processText(String text) {
            return (text.length() > maxLength) ? Label.TOO_LONG : Label.OK;
        }
    }

    public Label checkLabels(TextAnalyzer[] analyzers, String text) {
        for (TextAnalyzer analyzer : analyzers) {
            Label result;

            if ((result = analyzer.processText(text)) != Label.OK) {
                return result;
            }
        }

        return Label.OK;
    }
}
