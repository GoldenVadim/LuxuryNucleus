#include <graphics/vt/textcon/textcon.hpp>
#include <init/services/logger.hpp>
#include <memory/alloc.hpp>
#include <misc/str_int.hpp>
#include "logging.hpp"
#include "vt.hpp"
using namespace Miscellaneous;
using namespace Graphics;
using namespace Debug;

namespace LogPrefix
{
    static constexpr const char *const Info = "<*> ",
                                *const Warn = "<!> ",
                                *const Error  = "<X> ";
}

static char *buffer;
static void (*write_str)(const char *const &prefix, const char *const &str, const unsigned long long &len);
#define buffer_size 2000000
static unsigned long long buffer_len = 0;
bool Logging::inited = false;

static void __write_str_buffer_only(const char *const &prefix, const char *const &str, const unsigned long long &len)
{
    if (buffer_len + len + 4 > buffer_size)
        Memory::clean(buffer, buffer_len);
    Memory::copy_to(buffer + buffer_len, prefix, 4);
    buffer_len += 4;
    Memory::copy_to(buffer + buffer_len, str, len);
    buffer_len += len;
    buffer[buffer_len] = '\n';
    ++buffer_len;
}

static void __write_str_with_textcon(const char *const &prefix, const char *const &str, const unsigned long long &len)
{
    __write_str_buffer_only(prefix, str, len);
    VT::textcon::print(prefix, 4);
    VT::textcon::print(str, len);
    VT::textcon::put_char('\n');
}

void Logging::info(const char *const &text)
{
    write_str(LogPrefix::Info, text, Str_Int::length_of(text));
}

void Logging::warn(const char *const &text)
{
    write_str(LogPrefix::Warn, text, Str_Int::length_of(text));
}

void Logging::err(const char *const &text)
{
    write_str(LogPrefix::Error, text, Str_Int::length_of(text));
}

void Logging::switch_to_vt()
{
    write_str = __write_str_with_textcon;
    VT::textcon::print(buffer,buffer_len);
}

void Logging::init()
{
    buffer = Memory::allocate<char>(buffer_size);
    write_str = __write_str_buffer_only;
    inited = true;
    info("[debug/logger]: initialized buffer of 2 MB");
}