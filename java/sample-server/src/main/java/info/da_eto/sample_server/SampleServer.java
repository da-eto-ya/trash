package info.da_eto.sample_server;

import info.da_eto.sample_server.container.JettyEmbeddedRunner;

public class SampleServer {
    public static void main(final String[] args) {
        System.out.println("Starting Jetty ..");
        new JettyEmbeddedRunner().startServer();
    }
}
