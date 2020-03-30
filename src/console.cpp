#include <Arduino.h>

#include "console.h"

// Reads an array of 4 integers from a (well-formatted) IP string.
// The buffer passed should (at least) have 4 elements
static bool readIP(const char *ipString, int parts[]) {
    const char *s = ipString;
    parts[3] = -1;  // To detect if a valid IP was produced
    for (int i=0; i < 4; i++) {
        int v = atoi(s);
        if ((v >= 0) && (v <= 255)) {
            parts[i] = v;
            s = strchr(s, '.');
            if (s == NULL)
                break;
            s++;
        }
        else
            break;
    }
    return parts[3] >= 0;
}

enum State {
    INIT,
    CONFIG_NETWORK
};

State state = INIT;
int substate = 0;

Console::Console() {
    // Clear buffer (Set to empty string)
    buffer[0] = 0;
    bufferIndex = 0;
}

bool Console::readCommand() {
    const char *command = readLine();
    if (command)
    {
        Serial.print(F("Command: "));
        Serial.println(command);
        int parts[4];
        bool ipOK = readIP(command, parts);
        if (ipOK) {
            Serial.printf("IP: %d.%d.%d.%d\n", parts[0], parts[1], parts[2], parts[3]);
        }
        return true;
    }
    return false;
}

const char *Console::readLine() {
    // Read next byte if available
    while (Serial.available() > 0) {
        char b = (char)(Serial.read());
        if (b != '\r') {
            // Ignore returns
            if (b == '\n') {
                Serial.println();
                // End of line, send the string
                buffer[bufferIndex] = 0;    // Terminate string
                bufferIndex = 0;
                return buffer;
            }
            else {
                Serial.print(b);
                // Check buffer size
                if (bufferIndex >= (BUFSIZE - 1)) {
                    // Buffer full
                    buffer[bufferIndex] = 0;
                    bufferIndex = 0;
                    return "error: buffer overflow";
                }
                // Buffer size OK, append character
                buffer[bufferIndex++] = b;
            }
        }
    }
    // No command line, return null
    return NULL;
}
