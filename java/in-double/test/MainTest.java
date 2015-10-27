import java.io.ByteArrayInputStream;

import static org.junit.Assert.*;

public class MainTest {

    @org.junit.Test
    public void testSumInput() throws Exception {
        String[] in = {
                "1 2 3",
                "a1 b2 c3",
                "-1e3\n" + "18 .111 11bbb"
        };
        double[] out = {
                6.000000,
                0.000000,
                -981.889000,
        };

        Main main = new Main();

        for (int i = 0; i < in.length; i++) {
            assertEquals(out[i], main.sumInput(new ByteArrayInputStream(in[i].getBytes())), 1e-7);
        }
    }
}