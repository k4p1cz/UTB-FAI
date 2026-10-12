package utb.fai;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.Socket;
import java.net.UnknownHostException;
import java.nio.charset.StandardCharsets;

public class EmailSender implements AutoCloseable {
    private final Socket socket;
    private final BufferedReader reader;
    private final BufferedWriter writer;

    public EmailSender(String host, int port) throws UnknownHostException, IOException {
        socket = new Socket(host, port);
        reader = new BufferedReader(new InputStreamReader(socket.getInputStream(), StandardCharsets.UTF_8));
        writer = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream(), StandardCharsets.UTF_8));
        expectResponse(220);
    }

    public void send(String from, String to, String subject, String text) throws IOException {
        validateHeaderValue(from, "from");
        validateHeaderValue(to, "to");
        validateHeaderValue(subject, "subject");

        sendCommand("HELO localhost", 250);
        sendCommand("MAIL FROM:<" + from + ">", 250);
        sendCommand("RCPT TO:<" + to + ">", 250, 251);
        sendCommand("DATA", 354);

        writeLine("From: <" + from + ">");
        writeLine("To: <" + to + ">");
        writeLine("Subject: " + subject);
        writeLine("");
        writeMessageBody(text == null ? "" : text);
        writeLine(".");
        writer.flush();
        expectResponse(250);
    }

    @Override
    public void close() {
        if (!socket.isClosed()) {
            try {
                writer.write("QUIT\r\n");
                writer.flush();
                expectResponse(221);
            } catch (IOException ignored) {
                // Closing the socket is still required when the server has already disconnected.
            } finally {
                try {
                    socket.close();
                } catch (IOException ignored) {
                    // The socket is no longer usable.
                }
            }
        }
    }

    private void sendCommand(String command, int... acceptedCodes) throws IOException {
        writer.write(command);
        writer.write("\r\n");
        writer.flush();
        expectResponse(acceptedCodes);
    }

    private void expectResponse(int... acceptedCodes) throws IOException {
        String line = reader.readLine();
        if (line == null || line.length() < 3) {
            throw new IOException("SMTP server closed the connection or sent an invalid response");
        }

        int responseCode;
        try {
            responseCode = Integer.parseInt(line.substring(0, 3));
        } catch (NumberFormatException exception) {
            throw new IOException("Invalid SMTP response: " + line, exception);
        }

        while (line.length() > 3 && line.charAt(3) == '-') {
            line = reader.readLine();
            if (line == null || line.length() < 3) {
                throw new IOException("Incomplete multiline SMTP response");
            }
        }

        for (int acceptedCode : acceptedCodes) {
            if (responseCode == acceptedCode) {
                return;
            }
        }
        throw new IOException("Unexpected SMTP response: " + line);
    }

    private void writeMessageBody(String text) throws IOException {
        String normalized = text.replace("\r\n", "\n").replace('\r', '\n');
        if (normalized.isEmpty()) {
            return;
        }

        String[] lines = normalized.split("\n", -1);
        int lineCount = lines.length;
        if (normalized.endsWith("\n")) {
            lineCount--;
        }

        for (int index = 0; index < lineCount; index++) {
            String line = lines[index];
            if (line.startsWith(".")) {
                writer.write('.');
            }
            writeLine(line);
        }
    }

    private void writeLine(String line) throws IOException {
        writer.write(line);
        writer.write("\r\n");
    }

    private void validateHeaderValue(String value, String name) {
        if (value == null || value.indexOf('\r') >= 0 || value.indexOf('\n') >= 0) {
            throw new IllegalArgumentException("Invalid " + name + " value");
        }
    }
}