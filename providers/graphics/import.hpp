#include "info.hpp"

#define GPU_provider_import(NAME,PRINT_FUNC,INIT_FUNC,INIT_VAR) \
constexpr Providers::Graphics::GPU_provider_info _GPU_INFO_CARD__ ## NAME \
__attribute__((section(".providers.graphics"))) \
{ \
    .name = #NAME, \
    .inited = INIT_VAR, \
    .write_func = PRINT_FUNC, \
    .init_func = INIT_FUNC \
};
