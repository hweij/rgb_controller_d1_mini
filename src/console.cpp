#include <Arduino.h>

#include "console.h"

Console::Console() {
    // Clear buffer (Set to empty string)
    buffer[0] = 0;
    bufferIndex = 0;
}

const char *Console::readCommand() {
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
