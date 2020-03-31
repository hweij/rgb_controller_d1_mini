#include <EEPROM.h>

#include "config.h"

void Config::read()
{
    EEPROM.begin(512);
    // for (int i = 0; i < 512; i++)
    // {
    //     Serial.print(EEPROM.read(i));
    //     Serial.print(" ");
    // }
    // TEST TEST
    int numBytes = fromBytes(EEPROM.getConstDataPtr());
}

int Config::fromBytes(const uint8_t *bytes)
{
    int res = 0;
    magic = 0;
    for (int i = 0; i < 4; i++)
    {
        magic = (magic << 8) | bytes[i];
        res++;
    }
    res += networkConfig.fromBytes(bytes);
    // Accept the data only if the magic code matches. If not, initialize the config with a default.
    if (magic != MAGIC)
    {
        networkConfig.setDefault();
    }
    return res;
}

void NetworkConfig::readIP(int &index, int array[4], const uint8_t *bytes)
{
    for (int i = 0; i < 4; i++)
        array[i] = bytes[index++];
}

int NetworkConfig::fromBytes(const uint8_t *bytes)
{
    int res = 0;
    dhcp = bytes[res++];
    readIP(res, host, bytes);
    readIP(res, gateway, bytes);
    readIP(res, netmask, bytes);
    readIP(res, ns1, bytes);
    readIP(res, ns2, bytes);
    return res;
}

void NetworkConfig::setDefault()
{
    // It suffices to set dhcp to true since the other fields will not be needed
    dhcp = true;
}
