#include <arch/x86/pmio.hpp>
#include "ports.hpp"
using namespace Memory;

#if defined(__x86_64) || defined(__i386)
void (*const &Ports::write)(const unsigned short &port, const char &value) = Architecture::x86::out;
char (*const &Ports::read)(const unsigned short &port) = Architecture::x86::in;
#endif