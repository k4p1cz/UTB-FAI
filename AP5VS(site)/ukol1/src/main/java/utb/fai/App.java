package utb.fai;

import java.io.IOException;

public class App {
    public static void main(String[] args) {
        if (args.length != 6) {
            System.err.println("Usage: <smtp-host> <smtp-port> <from> <to> <subject> <text>");
            return;
        }

        try {
            int port = Integer.parseInt(args[1]);
            try (EmailSender sender = new EmailSender(args[0], port)) {
                sender.send(args[2], args[3], args[4], args[5]);
            }
        } catch (IOException | IllegalArgumentException exception) {
            System.err.println("Unable to send email: " + exception.getMessage());
        }
    }
}