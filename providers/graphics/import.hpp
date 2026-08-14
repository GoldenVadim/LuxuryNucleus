#include "info.hpp"

#define GPU_provider_import(GPU_CARD_INFO) \
static const Providers::Graphics::GPU __attribute__((section("providers.graphics"),used)) \
*const _GPU_INFO__ ## Name = &GPU_CARD_INFO;
