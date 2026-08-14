extern void setup_paging() asm("setup_paging");

static unsigned __attribute__((aligned(4096))) page_directory[1024];
static unsigned __attribute__((aligned(4096))) page_table[1024];

void setup_paging()
{
    unsigned i;
    for (i = 0; i != 1024; ++i)
        page_directory[i] = 0x2;
    for (i = 0; i < 1024; i++)
        page_table[i] = (i * 4096) | 3;
    page_directory[0] = reinterpret_cast<unsigned>(page_table) | 3;
    asm volatile
    (
        "mov cr3, %0\n"
        "mov eax, cr0\n"
        "and eax, 0x80000000\n"
        "mov cr0, eax"
        :
        : "r"(page_directory)
        : "memory"
    );
}