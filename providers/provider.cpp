#include <debug/logging.hpp>
#include "graphics/provide.hpp"
using namespace Providers;

extern const Graphics::GPU_provider_info providers_graphics_start[] asm("providers_graphics_start"),
                                         providers_graphics_end[] asm("providers_graphics_end");

const Graphics::GPU_provider_info *Providers::provide_gpu()
{
    static const Graphics::GPU_provider_info *ptr = providers_graphics_start;
    while (ptr < providers_graphics_end)
    {
        if (ptr)
        {
            if (ptr->name && ptr->init_func && ptr->write_func && ptr->inited)
            {
                if (!*ptr->inited)
                {
                    ptr->init_func();
                    break;
                }
            }
        }
    }
    if (ptr == providers_graphics_end) ptr = providers_graphics_start;
    return ptr;
}