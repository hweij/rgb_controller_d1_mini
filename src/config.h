// Describes a network configuration.
struct NetworkConfig
{
    bool dhcp;
    int host[4];
    int gateway[4];
    int netmask[4];
    int ns1[4];
    int ns2[4];

    private:
    void readIP(int &index, int array[4], const uint8_t *bytes) {
        for (int i=0; i<4; i++)
            array[i] = bytes[index++];
    }

    public:
    int fromBytes(const uint8_t *bytes) {
        int res = 0;
        dhcp = bytes[res++];
        readIP(res, host, bytes);
        readIP(res, gateway, bytes);
        readIP(res, netmask, bytes);
        readIP(res, ns1, bytes);
        readIP(res, ns2, bytes);
        return res;
    }
};

