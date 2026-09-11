#include <debug/logging.hpp>
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

void (*df)(unsigned i);

void init_main()
{
    Logging::init();
    Logging::info("Welcome to LuxuryNucleus...\1 | Built on " __DATE__ ", " __TIME__ " | Alpha ver.");
    Graphics::VT::init();
    while (not_crashed)
    {
        
    }
}