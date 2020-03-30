#include <Arduino.h>

#include "util.h"
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

// Describes a network configuration.
struct NetworkConfig {
    bool dhcp;
    int host[4];
    int gateway[4];
    int netmask[4];
    int ns1[4];
    int ns2[4];
};

static NetworkConfig networkConfig;

static State state = INIT;
static int subState = 0;

// Message strings in program memory
static const char strEnterHost[] PROGMEM = "Enter D for DHCP, or a static IP (xxx.xxx.xxx.xxx)";
// static const char strEnterGateway[] PROGMEM = "Enter gateway IP (Enter for %d.%d.%d.1)";
static const char strEnterNetmask[] PROGMEM = "Enter net mask (Enter for 255.255.255.0)";
static const char strEnterNS1[] PROGMEM = "Enter name server 1 (Enter for 8.8.8.8)";
static const char strEnterNS2[] PROGMEM = "Enter name server 2 (Enter for 8.8.4.4)";
static const char strConfirmNetwork[] PROGMEM = "Enter Y to confirm, N to cancel.";

Console::Console() {
    // Clear buffer (Set to empty string)
    buffer[0] = 0;
    bufferIndex = 0;
}

bool Console::readCommand() {
    const char *command = readLine();
    if (command)
    {
        switch (state) {
            case INIT: {
                if (startsWith(command, "config network")) {
                    state = CONFIG_NETWORK;
                    subState = 0;
                    Serial.println(FPSTR(strEnterHost));
                }
                else {
                    Serial.print(F("Command: "));
                    Serial.println(command);
                    int parts[4];
                    bool ipOK = readIP(command, parts);
                    if (ipOK) {
                        Serial.printf("IP: %d.%d.%d.%d\n", parts[0], parts[1], parts[2], parts[3]);
                    };
                }
            }
                break;
            case CONFIG_NETWORK:
                configNetwork(command);
                break;
        }
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

void Console::configNetwork(const char *command) {
    switch (subState) {
        case 0:
            // Ask for choice: Dhcp or IP address to assign a static IP
            if (startsWith(command, "D")) {
                networkConfig.dhcp = true;
                // Done
                state = INIT;
                subState = 0;
            }
            else {
                networkConfig.dhcp = false;
                // Static
                bool success = readIP(command, networkConfig.host);
                if (success) {
                    subState++;
                    Serial.printf("Enter gateway IP (Enter for %d.%d.%d.1)",
                        networkConfig.host[0], networkConfig.host[1], networkConfig.host[2]);
                }
                else {
                    Serial.println(FPSTR(strEnterHost));
                }
            }
            break;
        case 1: {
                bool success = readIP(command, networkConfig.gateway);
                if (success) {
                    subState++;
                    Serial.println(FPSTR(strEnterNetmask));
                }
                else {
                    Serial.printf("Enter gateway IP (Enter for %d.%d.%d.1)",
                        networkConfig.host[0], networkConfig.host[1], networkConfig.host[2]);
                }
            }
            break;
        case 2: {
                bool success = readIP(command, networkConfig.netmask);
                if (success) {
                    subState++;
                    Serial.println(FPSTR(strEnterNS1));
                }
                else {
                    Serial.println(FPSTR(strEnterNetmask));
                }
            }
            break;
        case 3: {
                bool success = readIP(command, networkConfig.ns1);
                if (success) {
                    subState++;
                    Serial.println(FPSTR(strEnterNS2));
                }
                else {
                    Serial.println(FPSTR(strEnterNS1));
                }
            }
            break;
        case 4: {
                bool success = readIP(command, networkConfig.ns2);
                if (success) {
                    // Done
                    subState++;
                    Serial.println(FPSTR(strConfirmNetwork));
                }
                else {
                    Serial.println(FPSTR(strEnterNS2));
                }
            }
            break;
        case 5:
            if (startsWith(command, "Y")) {
                Serial.println("Saving changes, restarting..");
            }
            else {
                Serial.println("Configuration canceled.");
            }
            state = INIT;
            subState = 0;
            break;
    }
}