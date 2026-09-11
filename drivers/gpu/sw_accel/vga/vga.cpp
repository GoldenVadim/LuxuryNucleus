/* 
   Legacy VGA framebuffer driver for legacy BIOS
*/

#include <drivers/bios/bda.hpp>
#include <debug/logging.hpp>
#include <memory/ports.hpp>
#include <providers/graphics/import.hpp>
#include <memory/alloc.hpp>
#include "vga_colors.hpp"
using namespace Miscellaneous::Graphics::GPU::VGA;
using namespace Drivers;
using namespace Memory;

#define mmio_addr_VGA_fb_text_colour     0xB8000
#define mmio_addr_VGA_fb_text_monochrome 0xB0000
#define mmio_addr_VGA_fb_graphics        0xA0000
#define VGA_text_width 80
#define VGA_text_height 25

// char *const vga_graphics_buffer = ;
static bool VGA_text_type_colour, VGA_text_inited = false, inited = false;
static unsigned short *VGA_text_buffer, VGA_text_entry_attribute;

static void VGA_text_put_entry(const char &entry, const unsigned short &X, const unsigned short &Y) 
{
	VGA_text_buffer[Y * VGA_text_width + X] = entry | VGA_text_entry_attribute;
}

static char VGA_text_get_entry(const unsigned short &X, const unsigned short &Y)
{
    return VGA_text_buffer[Y * 80 + X];
}

static void VGA_text_set_attr(const vga_colors &foreground, const vga_colors &background, const bool &blink)
{
    VGA_text_entry_attribute = (foreground | background << 4 | blink << 7) << 8;
}

static void enable_text_cursor(const char &high_scanline, const char &low_scanline)
{
    Ports::write(0x3D4, 0x0A);
	Ports::write(0x3D5, (Ports::read(0x3D5) & 0xC0) | high_scanline);

	Ports::write(0x3D4, 0x0B);
	Ports::write(0x3D5, (Ports::read(0x3D5) & 0xE0) | low_scanline);
}

static void disable_text_cursor()
{
	Ports::write(0x3D4, 0x0A);
	Ports::write(0x3D5, 0x20);
}

static void move_text_cursor(const unsigned short &X, const unsigned short &Y)
{
    const unsigned short pos = Y * VGA_text_width + X;
    Ports::write(0x3D4, 0x0F);
    Ports::write(0x3D5, pos & 0xFF);
    Ports::write(0x3D4, 0x0E);
    Ports::write(0x3D5, pos >> 8 & 0xFF);
}

static const Providers::Graphics::Display display_colour
{
    .name = "IBM PC-compatible unknown builtin colour VGA display",
    .width = 80,
    .height = 25,
    .update_freq = 0,
    .type_colour = true,
    .builtin = true,
}, display_monochrome
{
    .name = "IBM PC-compatible unknown builtin monochrome VGA display",
    .width = 80,
    .height = 25,
    .update_freq = 0,
    .type_colour = false,
    .builtin = true,
}, *displays = nullptr;

static void __attribute__((used)) init()
{
    if (!inited)
    {
        Debug::Logging::info("[gpu/vga]: initializing VGA text framebuffer...");
        BDA::vga_display_type type = BDA::get_vga_display_type();
        switch (type)
        {
            case BDA::vga_display_type::COLOUR:
                Debug::Logging::info("[gpu/vga]: detected colour video type");
                displays = &display_colour;
                VGA_text_type_colour = true;
                VGA_text_buffer = reinterpret_cast<unsigned short *>(mmio_addr_VGA_fb_text_colour);
                break;
            case BDA::vga_display_type::MONOCHROME:
                Debug::Logging::info("[gpu/vga]: detected monochrome video type");
                displays = &display_monochrome;
                VGA_text_type_colour = false;
                VGA_text_buffer = reinterpret_cast<unsigned short *>(mmio_addr_VGA_fb_text_monochrome);
                break;
            case BDA::vga_display_type::NONE:
                Debug::Logging::warn("[gpu/vga]: no video display present.");
                return;
            default:
                Debug::Logging::err("[gpu/vga]: failed to get video type");
                return;
        }
        disable_text_cursor();
        Memory::clean<unsigned short>(VGA_text_buffer,25 * 80 + 80);
        VGA_text_set_attr(LIGHT_GRAY, BLACK, 0);
        VGA_text_inited = true;
        enable_text_cursor(12, 14);
        move_text_cursor(0, 0);
        inited = true;
    }
}

static const Providers::Graphics::Framebuffer fbs[]
{
    {
        .name = "IBM PC-compatible BIOS VGA text framebuffer",
        .type_text = true,
        .type_colour = true,
        .max_width = 80,
        .max_height = 25,
        .inited = &VGA_text_inited,
        .cursor_set_func = move_text_cursor,
        .write_func = VGA_text_put_entry,
        .get_func = VGA_text_get_entry
    }
}, *const fbs_ptr = fbs;

static const Providers::Graphics::GPU __attribute__((used)) VGA
{
    .name = "IBM PC-compatible VGA software-acceleration GPU",
    .sw_accel = true,
    .inited = &inited,
    .displays = &displays,
    .displays_len = 1,
    .primary_display = 0,
    .fbs = &fbs_ptr,
    .fbs_len = 1,
    .init_func = init
};

GPU_provider_import(VGA)