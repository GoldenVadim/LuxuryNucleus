#include <providers/graphics/provide.hpp>
#include <init/services/vt.hpp>
#include <debug/logging.hpp>
#include <misc/str_int.hpp>
#include "textcon/vt.hpp"
#include <debug/vt.hpp>
using namespace Graphics;

static const Providers::Graphics::Framebuffer *text_fb, *graphics_fb;
void (*VT::move_cursor)(const unsigned short &X, const unsigned short &Y);
void (*VT::put_entry)(const char &, const unsigned short &X, const unsigned short &Y);
char (*VT::get_entry)(const unsigned short &X, const unsigned short &Y);
bool VT::text_mode = false, VT::native_text = false;
const unsigned short *VT::width, *VT::height;

static void vt_update_mode()
{
    if (VT::text_mode)
    {
        VT::put_entry = graphics_fb->write_func;
        VT::get_entry = graphics_fb->get_func;
        //
    }
    else
    {
        VT::put_entry = text_fb->write_func;
        VT::get_entry = text_fb->get_func;
        VT::move_cursor = text_fb->cursor_set_func;
        Debug::Logging::switch_to_vt();
    }
    VT::text_mode = !VT::text_mode;
}

void VT::init()
{
    Debug::Logging::info("[vt]: getting gpu...");
    static Providers::Graphics::GPU *gpu = Providers::Graphics::gpu();
    Debug::Logging::info(gpu->name);
    if (!*gpu->inited)
    {
        Debug::Logging::info("[vt]: initializing this gpu...");
        gpu->init_func();
    }
    Debug::Logging::info("[vt]: checking framebuffers...");
    for (unsigned i = 0; i != gpu->fbs_len; ++i)
    {
        Debug::Logging::info(gpu->fbs[i]->name);
        if (*gpu->fbs[i]->inited)
        {
            if (gpu->fbs[i]->type_text)
            {
                Debug::Logging::info("[vt]: this fb natively supports only text characters.");
                text_fb = &*gpu->fbs[i];
                native_text = true;
            }
            else
                graphics_fb = &*gpu->fbs[i];
            if (!width && !height)
            {
                width = &gpu->fbs[i]->max_width;
                height = &gpu->fbs[i]->max_height;
            }
        }
        else
        {
            Debug::Logging::warn("[vt]: not active");
            continue;
        }
    }
    if (!graphics_fb && text_fb)
        Debug::Logging::warn("[vt]: only text mode is available");
    Debug::Logging::info("[vt]: checking displays...");
    for (unsigned i = 0; i != gpu->displays_len; ++i)
    {
        Debug::Logging::info(gpu->displays[i]->name);
        if (gpu->displays[i]->builtin && gpu->sw_accel && gpu->displays_len == 1
            && *width == gpu->displays[i]->width && *height == gpu->displays[i]->height)
            Debug::Logging::warn("[vt]: maybe this GPU doesn't support variable displays.");
        if (!gpu->displays[i]->type_colour)
            Debug::Logging::warn("[vt]: this display is monochrome.");
    }
    vt_update_mode();
}
