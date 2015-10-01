public class Roles {
    public static void main(String[] args) {
        String[] roles = {
                "Городничий",
                "Аммос Федорович",
                "Артемий Филиппович",
                "Лука Лукич"
        };
        String[] textLines = {
                "Городничий: Я пригласил вас, господа, с тем, чтобы сообщить вам пренеприятное известие: к нам едет ревизор.",
                "Аммос Федорович: Как ревизор?",
                "Артемий Филиппович: Как ревизор?",
                "Городничий: Ревизор из Петербурга, инкогнито. И еще с секретным предписаньем.",
                "Аммос Федорович: Вот те на!",
                "Артемий Филиппович: Вот не было заботы, так подай!",
                "Лука Лукич: Господи боже! еще и с секретным предписаньем!"
        };
        System.out.println(printTextPerRole(roles, textLines));
    }

    private static String printTextPerRole(String[] roles, String[] textLines) {
        String[] prefixes = new String[roles.length];

        for (int i = 0; i < roles.length; i++) {
            prefixes[i] = roles[i] + ":";
        }

        StringBuilder[] builders = new StringBuilder[prefixes.length];

        for (int i = 0; i < prefixes.length; i++) {
            builders[i] = new StringBuilder(prefixes[i]);
        }

        for (int i = 0; i < textLines.length; i++) {
            for (int j = 0; j < prefixes.length; j++) {
                if (textLines[i].startsWith(prefixes[j])) {
                    builders[j].append("\n").append(i + 1).append(")")
                            .append(textLines[i].substring(prefixes[j].length()));
                    break;
                }
            }
        }

        StringBuilder res = new StringBuilder("");

        for (int i = 0; i < builders.length; i++) {
            res.append(builders[i]).append("\n\n");
        }

        return res.toString();
    }
}
