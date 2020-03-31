static const int BUFSIZE = 100;

enum State
{
    INIT,
    CONFIG_NETWORK
};

class Console {
    public:
        Console();
        void init();
        bool readCommand();
    private:
        char buffer[BUFSIZE];
        int bufferIndex;
        State state;
        int subState = 0;
        // Reads from Serial and returns a line of input when the users hit returns.
        // If no complete line has been read, NULL is returned.
        // If the internal buffer overflows, a text signalling this is returned.
        // The data rturned are owned by this class, do not modify it.
        const char *readLine();
        void setState(State s, int sub);
};
