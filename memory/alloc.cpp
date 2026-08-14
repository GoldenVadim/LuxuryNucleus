#include "alloc.hpp"

extern char mmio_addr_alloc_kernel_end[] asm("mmio_addr_alloc_kernel_end");

void* Memory::__malloc(const unsigned long long &size)
{
    char *ptr = nullptr;
    if (size > 1)
    {
        ptr = mmio_addr_alloc_kernel_end;
        bool give_this; unsigned long long i;
        while (true)
        {
            give_this = true;
            for (i = 0; i != size; ++i)
            {
                if (ptr[i]) // != zero
                    give_this = false;
                else if (!give_this)
                    break;
            }
            ptr += i;
            if (give_this)
                break;
        }
    }
    return ptr;
}

void Memory::__copy(char *const &dst, const char *const &src, const unsigned long long &size)
{
    for (unsigned long long _ = 0; _ != size; ++_)
        dst[_] = src[_];    
}