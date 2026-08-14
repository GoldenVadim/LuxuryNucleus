#include <debug/logging.hpp>

#ifdef __GNUG__

extern void debug_trace_function_enter(void *target, void *caller) asm("__cyg_profile_func_enter");
extern void debug_trace_function_exit(void *target, void *caller) asm("__cyg_profile_func_exit");

#endif

void __attribute__((no_instrument_function)) debug_trace_function_enter(void *target, void *caller)
{
    
}

void __attribute__((no_instrument_function)) debug_trace_function_exit(void *target, void *caller)
{
    
}