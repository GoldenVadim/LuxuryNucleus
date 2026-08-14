#include <memory/alloc.hpp>
#include "bda.hpp"
using namespace Drivers;

#define mmio_addr_bda 0x410
static const unsigned short *const bda_detected_hw = reinterpret_cast<const unsigned short *>(mmio_addr_bda);

BDA::vga_display_type BDA::get_vga_display_type()
{
    return static_cast<vga_display_type>(*bda_detected_hw & 0x30);
}