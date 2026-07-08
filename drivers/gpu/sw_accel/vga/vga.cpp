/* 
VGA text framebuffer driver for legacy BIOS
*/

#include <drivers/bios/bda.hpp>
#include <debug/logging.hpp>
#include <memory/io/port.hpp>
#include <memory/alloc.hpp>
#include <providers/graphics/import.hpp>
#include <library/str_int.hpp>
#include "vga_colors.hpp"
using namespace Miscellaneous::Graphics::GPU::VGA;
using namespace Drivers;
using namespace Memory::IO;
using namespace Library;

const unsigned short pmio_addr_vga_register_port_1 = 0x3D4;
const unsigned short pmio_addr_vga_register_port_2 = 0x3D5;
#define mmio_addr_vga_text_fb_colour     0xB8000
#define mmio_addr_vga_text_fb_monochrome 0xB0000
#define mmio_addr_vga_graphics_fb        0xA0000
#define vga_width 80
#define vga_height 25

bool inited = false, newline_at_end;
// char *const vga_graphics_buffer = ;
unsigned short *vga_text_buffer,
               *vga_text_scroll_buffer,
               attribute;
char X = 0, Y = 0;

static void put_entry(const unsigned short entry) 
{
	vga_text_buffer[Y * vga_width + X] = entry | attribute;
}

static void fill_with_zeros()
{
    for (X = 0; X != vga_width; X++)
	    put_entry(0);
    X = 0;
}

static void set_attr(const enum vga_colors &foreground, const enum vga_colors &background, const bool &blink)
{
    attribute = (foreground | background << 4 | blink << 7) << 8;
}

/*
static void enable_cursor(const char &high_scanline, const char &low_scanline)
{
    Ports::write(pmio_addr_vga_register_port_1, 0x0A);
	Ports::write(pmio_addr_vga_register_port_2, (Ports::read(pmio_addr_vga_register_port_2) & 0xC0) | high_scanline);

	Ports::write(pmio_addr_vga_register_port_1, 0x0B);
	Ports::write(pmio_addr_vga_register_port_2, (Ports::read(pmio_addr_vga_register_port_2) & 0xE0) | low_scanline);
}
*/

static void disable_cursor()
{
	Ports::write(pmio_addr_vga_register_port_1, 0x0A);
	Ports::write(pmio_addr_vga_register_port_2, 0x20);
}

static void clean()
{
    set_attr(LIGHT_GRAY, BLACK, 0);
    disable_cursor();
    for (Y = 0; Y != vga_height; Y++)
        fill_with_zeros();
    Y = 0;
}

static void scroll()
{
    for (Y = 0; Y != vga_height; Y++)
    {
        char row_width = Y * vga_width;
        for (X = 0; X != vga_width; X++)
            vga_text_scroll_buffer[X] = vga_text_buffer[row_width + X];
        Y--;

        for (X = 0; X != vga_width; X++)
            put_entry(vga_text_scroll_buffer[X]);
        Y++;
    }
    Y = 24;
    fill_with_zeros();
}

static void put_char(const char &what)
{
    switch (what)
    {
        case '\r': 
            X = 0;
            break;
        case '\n':
            Y++; X = 0;
            break;
        default:
            if (newline_at_end)
            {
                scroll();
                newline_at_end = false;
            }
            put_entry(what);
            if (X++ == vga_width) Y++;
            break;
    }
	if (Y == vga_height) newline_at_end = true;
}

static void init()
{
    if (!inited)
    {
        Debug::Logging::info("[vga/text]: checking video type in BDA...");
        enum BDA::vga_display_type type = BDA::get_vga_display_type();
        switch (type)
        {
            case BDA::vga_display_type::COLOUR:
                Debug::Logging::info("[vga/text]: detected colour video type");
                vga_text_buffer = reinterpret_cast<unsigned short *>(mmio_addr_vga_text_fb_colour);
                break;
            case BDA::vga_display_type::MONOCHROME:
                Debug::Logging::info("[vga/text]: detected monochrome video type");
                vga_text_buffer = reinterpret_cast<unsigned short *>(mmio_addr_vga_text_fb_monochrome);
                break;
            case BDA::vga_display_type::NONE:
                Debug::Logging::warn("[vga/text]: video display is not present.");
                return;
            default:
                Debug::Logging::err("[vga/text]: failed to get video type");
                return;
        }
        vga_text_scroll_buffer = Memory::allocate<unsigned short>(80);
        clean();
        inited = true;
    }
}

GPU_provider_import(VGA,put_char,init,&inited)