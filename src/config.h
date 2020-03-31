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
    void readIP(int &index, int array[4], const uint8_t *bytes);

public:
    int fromBytes(const uint8_t *bytes);
    void setDefault();
};

struct Config
{
public:
    const uint32_t MAGIC = 0xF480C317;
    uint32_t magic;
    NetworkConfig networkConfig;

    void read();
    int fromBytes(const uint8_t *bytes);

private:
};
