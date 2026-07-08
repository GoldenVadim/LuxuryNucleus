#include <debug/logging.hpp>
#include <providers/graphics/provide.hpp>
#include <init/services/fbcon.hpp>
#include "fbcon.hpp"
using namespace Graphics::fbcon;

//constexpr char log_prefix[10] = "[fbcon]: ";
void (*Graphics::fbcon::draw_char_gpu_func)(const char&);

static void set_primary_gpu(void (*const func)(const char&)){
    Debug::Logging::info("[graphics/fbcon]: setting primary GPU...");
    draw_char_gpu_func = func;
}

void Graphics::fbcon::init()
{
    Debug::Logging::info("[graphics/fbcon]: choosing GPU helper...");
    const Providers::Graphics::GPU_provider_info *info_card = Providers::provide_gpu();
    Debug::Logging::info(info_card->name);
    set_primary_gpu(info_card->write_func);
    if (draw_char_gpu_func != nullptr)
        switch_write_char_func();
    else
        Debug::Logging::warn("[graphics/fbcon]: no active GPU was detected");
}