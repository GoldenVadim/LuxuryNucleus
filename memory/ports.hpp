namespace Memory
{
    namespace Ports
    {
        extern void (*const &write)(const unsigned short &port, const char &value);
        extern char (*const &read)(const unsigned short &port);
    }
}