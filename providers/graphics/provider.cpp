#include <debug/logging.hpp>
#include "provide.hpp"
using namespace Providers;

extern Graphics::GPU *providers_graphics_start[] asm("providers_graphics_start"),
                     *providers_graphics_end[] asm("providers_graphics_end");

Graphics::GPU *Providers::Graphics::gpu()
{
    static Graphics::GPU *ptr = *providers_graphics_start;
    while (ptr < *providers_graphics_end)
    {
        if (ptr)
        {
            break;
        }
    }
    if (ptr == *providers_graphics_end) ptr = *providers_graphics_start;
    return ptr;
}