import java.util.logging.*;

public class SimpleLogging {
    public static final String AUSTIN_POWERS = "Austin Powers";
    public static final String WEAPONS = "weapons";
    public static final String BANNED_SUBSTANCE = "banned substance";

    /**
     * Интерфейс: сущность, которую можно отправить по почте.
     * У такой сущности можно получить от кого и кому направляется письмо.
     */
    public static interface Sendable {
        String getFrom();

        String getTo();
    }

    /**
     * Абстрактный класс,который позволяет абстрагировать логику хранения
     * источника и получателя письма в соответствующих полях класса.
     */
    public static abstract class AbstractSendable implements Sendable {
        protected final String from;
        protected final String to;

        public AbstractSendable(String from, String to) {
            this.from = from;
            this.to = to;
        }

        @Override
        public String getFrom() {
            return from;
        }

        @Override
        public String getTo() {
            return to;
        }

        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (o == null || getClass() != o.getClass()) return false;

            AbstractSendable that = (AbstractSendable) o;

            if (!from.equals(that.from)) return false;
            if (!to.equals(that.to)) return false;

            return true;
        }
    }

    /**
     * Письмо, у которого есть текст, который можно получить с помощью метода `getMessage`
     */
    public static class MailMessage extends AbstractSendable {
        private final String message;

        public MailMessage(String from, String to, String message) {
            super(from, to);
            this.message = message;
        }

        public String getMessage() {
            return message;
        }

        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (o == null || getClass() != o.getClass()) return false;
            if (!super.equals(o)) return false;

            MailMessage that = (MailMessage) o;

            if (message != null ? !message.equals(that.message) : that.message != null) return false;

            return true;
        }
    }

    /**
     * Посылка, содержимое которой можно получить с помощью метода `getContent`
     */
    public static class MailPackage extends AbstractSendable {
        private final Package content;

        public MailPackage(String from, String to, Package content) {
            super(from, to);
            this.content = content;
        }

        public Package getContent() {
            return content;
        }

        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (o == null || getClass() != o.getClass()) return false;
            if (!super.equals(o)) return false;

            MailPackage that = (MailPackage) o;

            if (!content.equals(that.content)) return false;

            return true;
        }
    }

    /**
     * Класс, который задает посылку. У посылки есть
     * текстовое описание содержимого и целочисленная ценность.
     */
    public static class Package {
        private final String content;
        private final int price;

        public Package(String content, int price) {
            this.content = content;
            this.price = price;
        }

        public String getContent() {
            return content;
        }

        public int getPrice() {
            return price;
        }

        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (o == null || getClass() != o.getClass()) return false;

            Package aPackage = (Package) o;

            if (price != aPackage.price) return false;
            if (!content.equals(aPackage.content)) return false;

            return true;
        }
    }

    /**
     * Интерфейс, который задает класс, который может
     * каким-либо образом обработать почтовый объект.
     */
    public static interface MailService {
        Sendable processMail(Sendable mail) throws IllegalPackageException, StolenPackageException;
    }

    /**
     * Класс, в котором скрыта логика настоящей почты
     */
    public static class RealMailService implements MailService {
        @Override
        public Sendable processMail(Sendable mail) {
            // Здесь описан код настоящей системы отправки почты.
            return mail;
        }
    }

    /**
     * Класс, моделирующий ненадежного работника почты, который вместо того,
     * чтобы передать почтовый объект непосредственно в сервис почты,
     * последовательно передает этот объект набору третьих лиц, а затем,
     * в конце концов, передает получившийся объект непосредственно экземпляру RealMailService.
     */
    public static class UntrustworthyMailWorker implements MailService {
        private final MailService[] others;
        private final RealMailService realMailService;

        public UntrustworthyMailWorker(MailService[] others) {
            this.others = others;
            this.realMailService = new RealMailService();
        }

        public RealMailService getRealMailService() {
            return realMailService;
        }

        @Override
        public Sendable processMail(Sendable mail) {
            for (MailService service : others) {
                mail = service.processMail(mail);
            }

            return realMailService.processMail(mail);
        }
    }

    /**
     * Шпион, который логгирует о всей почтовой переписке, которая проходит через его руки.
     * Объект конструируется от экземпляра Logger, с помощью которого шпион будет сообщать о всех действиях.
     * Он следит только за объектами класса MailMessage и пишет в логгер следующие сообщения
     * (в выражениях нужно заменить части в фигурных скобках на значения полей почты):
     * <p>
     * 2.1) Если в качестве отправителя или получателя указан "Austin Powers",
     * то нужно написать в лог сообщение с уровнем WARN:
     * Detected target mail correspondence: from {from} to {to} "{message}"
     * <p>
     * 2.2) Иначе, необходимо написать в лог сообщение с уровнем INFO:
     * Usual correspondence: from {from} to {to}
     */
    public static class Spy implements MailService {
        private final Logger logger;

        public Spy(Logger logger) {
            this.logger = logger;
        }

        @Override
        public Sendable processMail(Sendable mail) {
            if (mail instanceof MailMessage) {
                if (mail.getFrom().equals(AUSTIN_POWERS) || mail.getTo().equals(AUSTIN_POWERS)) {
                    logger.log(Level.WARNING,
                            "Detected target mail correspondence: from {0} to {1} \"{2}\"",
                            new Object[]{mail.getFrom(), mail.getTo(), ((MailMessage) mail).getMessage()}
                    );
                } else {
                    logger.log(Level.INFO,
                            "Usual correspondence: from {0} to {1}",
                            new Object[]{mail.getFrom(), mail.getTo()}
                    );
                }
            }

            return mail;
        }
    }

    /**
     * Вор, который ворует самые ценные посылки и игнорирует все остальное.
     * <p>
     * Вор принимает в конструкторе переменную int – минимальную стоимость посылки, которую он будет воровать.
     * <p>
     * Также, в данном классе должен присутствовать метод getStolenValue,
     * который возвращает суммарную стоимость всех посылок, которые он своровал.
     * <p>
     * Воровство происходит следующим образом: вместо посылки, которая пришла вору, он отдает новую,
     * такую же, только с нулевой ценностью и содержимым посылки "stones instead of {content}".
     */
    public static class Thief implements MailService {
        private final int minPrice;
        private int stolenValue;

        public Thief(int minPrice) {
            this.minPrice = minPrice;
            this.stolenValue = 0;
        }

        public int getStolenValue() {
            return stolenValue;
        }

        @Override
        public Sendable processMail(Sendable mail) {
            if (mail instanceof MailPackage) {
                Package aPackage = ((MailPackage) mail).getContent();

                if (aPackage.getPrice() >= minPrice) {
                    mail = new MailPackage(
                            mail.getFrom(),
                            mail.getTo(),
                            new Package("stones instead of " + aPackage.getContent(), 0)
                    );

                    stolenValue += aPackage.getPrice();
                }
            }

            return mail;
        }
    }

    /**
     * Инспектор, который следит за запрещенными и украденными посылками и бьет тревогу в виде исключения,
     * если была обнаружена подобная посылка.
     * <p>
     * Если он заметил запрещенную посылку с одним из запрещенных содержимым ("weapons" и "banned substance"),
     * то он бросает IllegalPackageException.
     * <p>
     * Если он находит посылку, состаящую из камней (содержит слово "stones"),
     * то тревога прозвучит в виде StolenPackageException.
     * <p>
     * Оба исключения вы должны объявить самостоятельно в виде непроверяемых исключений.
     */
    public static class Inspector implements MailService {

        @Override
        public Sendable processMail(Sendable mail) {
            if (mail instanceof MailPackage) {
                Package aPackage = ((MailPackage) mail).getContent();

                if (aPackage.getContent().contains(WEAPONS) || aPackage.getContent().contains(BANNED_SUBSTANCE)) {
                    throw new IllegalPackageException("weapons or banned substance");
                }

                if (aPackage.getContent().contains("stones")) {
                    throw new StolenPackageException("stones in mail");
                }
            }

            return mail;
        }
    }

    public static class IllegalPackageException extends RuntimeException {
        public IllegalPackageException() {
        }

        public IllegalPackageException(String message) {
            super(message);
        }

        public IllegalPackageException(String message, Throwable cause) {
            super(message, cause);
        }

        public IllegalPackageException(Throwable cause) {
            super(cause);
        }

        public IllegalPackageException(String message, Throwable cause, boolean enableSuppression, boolean writableStackTrace) {
            super(message, cause, enableSuppression, writableStackTrace);
        }
    }

    public static class StolenPackageException extends RuntimeException {
        public StolenPackageException() {
        }

        public StolenPackageException(String message) {
            super(message);
        }

        public StolenPackageException(String message, Throwable cause) {
            super(message, cause);
        }

        public StolenPackageException(Throwable cause) {
            super(cause);
        }

        public StolenPackageException(String message, Throwable cause, boolean enableSuppression, boolean writableStackTrace) {
            super(message, cause, enableSuppression, writableStackTrace);
        }
    }

    public static void main(String[] args) {

    }
}