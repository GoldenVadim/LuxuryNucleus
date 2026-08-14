#include <debug/logging.hpp>

void __attribute__((interrupt)) ISR_handler(char *sp, int f)
{
    Debug::Logging::err("d");
}