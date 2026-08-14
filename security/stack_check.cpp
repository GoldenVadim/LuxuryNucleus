#include <debug/logging.hpp>
#include <memory/alloc.hpp>

extern void stack_security_failure() asm(
#ifdef __GNUG__
"__stack_chk_fail"
#elif _MSC_BUILD
"__security_check_cookie"
#endif
);

void stack_security_failure()
{
    Debug::Logging::err("STACK SMASHING DETECTED!");
    //asm
    //(
    //    "mov esp, offset stack_top"
    //);
}