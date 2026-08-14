#ifdef __GNUG__

extern bool CXA_security_acquire(char *) asm("__cxa_guard_acquire");
extern void CXA_security_release(char *) asm("__cxa_guard_release");

#endif // __GNUG__

bool CXA_security_acquire(char *__cxa_guard)
{
    if (!__cxa_guard[0])
    {
        while (__cxa_guard[1]){}
        __cxa_guard[1] = true;
        return true;
    }
    return false;
}

void CXA_security_release(char *__cxa_guard)
{
    if (!__cxa_guard[0] && __cxa_guard[1])
    {
        __cxa_guard[0] = true;
        __cxa_guard[1] = false;
    }
}