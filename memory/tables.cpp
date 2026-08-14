#include <memory/alloc.hpp>

extern void setup_tables() asm("setup_tables");

static unsigned long long GDT[8192], IDT[256];
struct
{
    const unsigned short Size;
    unsigned long long Offset;
} GDTR
{
    .Size = 65535,
    .Offset = reinterpret_cast<unsigned long long>(&GDT)
}, IDTR
{
    .Size = 255,
    .Offset = reinterpret_cast<unsigned long long>(&IDT)
};

unsigned long long &gdt_addr = GDTR.Offset, &idt_addr = IDTR.Offset;

void setup_tables()
{
    asm volatile
    (
        "lgdt [%0]\n\t"
        "lidt [%1]"
        :
        : "r"(&GDTR), "r"(&IDTR)
        : "memory"
    );
}