#include <debug/logging.hpp>

#ifdef __i386
void __attribute__((interrupt)) ISR_handler(char *sp, unsigned f)
#else
void __attribute__((interrupt)) ISR_handler(char *sp, unsigned long long f)
#endif
{
    Debug::Logging::err("d");
}