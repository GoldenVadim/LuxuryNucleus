#include "multiboot2.hpp"
using namespace Architecture::x86::Multiboot2;

static constexpr header __attribute__((section(".headers.multiboot2"))) multiboot_hdr
{
    .magic = 0xE85250D6,
    .architecture = 0,
    .length = sizeof(header),
    .checksum = static_cast<unsigned>(-(0xE85250D6 + sizeof(header))),
    .tags
    {
        TAG(0,0,8)
    }
};