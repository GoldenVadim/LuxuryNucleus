#include <debug/logging.hpp>
#include <memory/tables.hpp>
#include <misc/str_int.hpp>
#include "services/logger.hpp"
#include "services/vt.hpp"
using namespace Miscellaneous::Str_Int;
using namespace Debug;

extern void init_main() asm("init_main");
extern char mmio_addr_alloc_kernel_start[],
            mmio_addr_alloc_bss_start[], mmio_addr_alloc_bss_end[],
            mmio_addr_alloc_rodata_start[], mmio_addr_alloc_rodata_end[],
            mmio_addr_alloc_text_start[], mmio_addr_alloc_text_end[],
            mmio_addr_alloc_data_start[], mmio_addr_alloc_data_end[],
            mmio_addr_alloc_kernel_end[];

static bool not_crashed = true;

void init_main()
{
    Logging::init();
    Logging::info("Welcome to LuxuryNucleus... | Built on " __DATE__ ", " __TIME__);
    if (gdt_addr && idt_addr)
    {
        Logging::info("GDT address:");
        Logging::info(to_string(gdt_addr,16,0));
        Logging::info("IDT address:");
        Logging::info(to_string(idt_addr,16,0));
    }
    else
        Logging::warn("GDT and IDT are not active!");
    Graphics::VT::init();

    while (not_crashed)
    {
        
    }
}