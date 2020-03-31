#include <Arduino.h>

#include "util.h"
#include "config.h"
#include "console.h"

NetworkConfig networkConfig;

// Reads an array of 4 integers from a (well-formatted) IP string.
// The buffer passed should (at least) have 4 elements
static bool readIP(const char *ipString, int parts[])
{
    const char *s = ipString;
    parts[3] = -1; // To detect if a valid IP was produced
    for (int i = 0; i < 4; i++)
    {
        int v = atoi(s);
        if ((v >= 0) && (v <= 255))
        {
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

// Message strings in program memory
static const char strEnterCommand[] PROGMEM = "Enter command";
static const char strEnterHost[] PROGMEM = "Enter D for DHCP, or a static IP (xxx.xxx.xxx.xxx)";
// static const char strEnterGateway[] PROGMEM = "Enter gateway IP (Enter for %d.%d.%d.1)";
static const char strEnterNetmask[] PROGMEM = "Enter net mask (Enter for 255.255.255.0)";
static const char strEnterNS1[] PROGMEM = "Enter name server 1 (Enter for 8.8.8.8)";
static const char strEnterNS2[] PROGMEM = "Enter name server 2 (Enter for 8.8.4.4)";
static const char strConfirmNetwork[] PROGMEM = "Enter Y to confirm, N to cancel.";

void setState(State s, int sub);

Console::Console()
{
}

void Console::init() {
    setState(INIT, 0);
}

void Console::setState(State s, int sub)
{
    state = s;
    subState = sub;
    switch (state)
    {
    case INIT:
        Serial.println(FPSTR(strEnterCommand));
        break;
    case State::CONFIG_NETWORK:
        switch (subState)
        {
        case 0:
            Serial.println(FPSTR(strEnterHost));
            break;
        case 1:
            Serial.printf("Enter gateway IP (Enter for %d.%d.%d.1)",
                          networkConfig.host[0], networkConfig.host[1], networkConfig.host[2]);
            break;
        case 2:
            Serial.println(FPSTR(strEnterNetmask));
            break;
        case 3:
            Serial.println(FPSTR(strEnterNS1));
            break;
        case 4:
            Serial.println(FPSTR(strEnterNS2));
            break;
        case 5:
            Serial.println(FPSTR(strConfirmNetwork));
            break;
        }
    }
}

bool Console::readCommand()
{
    const char *command = readLine();
    if (command)
    {
        switch (state)
        {
        case INIT:
            if (startsWith(command, "config network"))
            {
                state = CONFIG_NETWORK;
                subState = 0;
                Serial.println(FPSTR(strEnterHost));
            }
            else
            {
                Serial.print(F("Command: "));
                Serial.println(command);
                int parts[4];
                bool ipOK = readIP(command, parts);
                if (ipOK)
                {
                    Serial.printf("IP: %d.%d.%d.%d\n", parts[0], parts[1], parts[2], parts[3]);
                };
            }
        break;
        case CONFIG_NETWORK:
            switch (subState)
            {
            case 0:
                // Ask for choice: Dhcp or IP address to assign a static IP
                if (startsWith(command, "D"))
                {
                    networkConfig.dhcp = true;
                    // Done
                    setState(INIT, 0);
                }
                else
                {
                    networkConfig.dhcp = false;
                    // Static
                    setState(state, readIP(command, networkConfig.host) ? subState + 1 : subState);
                }
                break;
            case 1:
                setState(state, readIP(command, networkConfig.gateway) ? subState + 1 : subState);
                break;
            case 2:
                setState(state, readIP(command, networkConfig.netmask) ? subState + 1 : subState);
                break;
            case 3:
                setState(state, readIP(command, networkConfig.ns1) ? subState + 1 : subState);
                break;
            case 4:
                setState(state, readIP(command, networkConfig.ns2) ? subState + 1 : subState);
                break;
            case 5:
                if (startsWith(command, "Y"))
                {
                    Serial.println("Saving changes, restarting..");
                }
                else
                {
                    Serial.println("Configuration canceled.");
                }
                setState(INIT, 0);
                break;
            }
            break;
        }
    }
    return false;
}

const char *Console::readLine()
{
    // Read next byte if available
    while (Serial.available() > 0)
    {
        char b = (char)(Serial.read());
        if (b != '\r')
        {
            // Ignore returns
            if (b == '\n')
            {
                Serial.println();
                // End of line, send the string
                buffer[bufferIndex] = 0; // Terminate string
                bufferIndex = 0;
                return buffer;
            }
            else
            {
                Serial.print(b);
                // Check buffer size
                if (bufferIndex >= (BUFSIZE - 1))
                {
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
