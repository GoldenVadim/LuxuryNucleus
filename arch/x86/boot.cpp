extern void init_boot() asm("init_boot");
extern void init_main() asm("init_main");

char __attribute__((alignas(16))) stack[16384];

void init_boot()
{
    asm volatile
    (
        "lea esp, %0"
        :
        : "m"(stack[16384])
        : "memory"
    );

    init_main();
}