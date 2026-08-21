extern void setup_tables() asm("setup_tables");

static struct
{
    const unsigned short Size;
    unsigned long long Offset;
} GDTR
{
    .Size = 65535,
    .Offset = 0
}, IDTR
{
    .Size = 255,
    .Offset = 0
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