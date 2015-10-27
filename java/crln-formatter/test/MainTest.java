import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;

import static org.junit.Assert.*;

public class MainTest {
    private static final byte[][][] cases = new byte[][][]{
            {{65, 13, 10, 10, 13}, {65, 10, 10, 13}},
            {{65, 13, 13, 13, 10}, {65, 13, 13, 10}},
            {{65, 13, 10, 13, 10}, {65, 10, 10}},
            {{65, 13, 10, 13, 10, 26}, {65, 10, 10, 26}},
            {{13, 10}, {10}},
            {{13, 13, 13, 10, 13, 13}, {13, 13, 10, 13, 13}},
            {{}, {}},
            {{13}, {13}},
            {{10}, {10}},
            {{1}, {1}},
            {{10, 13}, {10, 13}},
    };

    @org.junit.Test
    public void testReplaceCRLN() throws Exception {
        for (byte[][] c : cases) {
            ByteArrayInputStream in = new ByteArrayInputStream(c[0]);
            ByteArrayOutputStream out = new ByteArrayOutputStream(c[0].length);

            new Main().replaceCRLN(in, out);

            assertArrayEquals(c[1], out.toByteArray());
        }
    }
}