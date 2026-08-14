#include <misc/str_int.hpp>
using namespace Miscellaneous;

char *EPS = reinterpret_cast<char *>(0xF0000);

enum
{
    bit32_size = 4,
    bit64_size = 5
};
static unsigned i, len;
static char checksum = 0;

static bool chksum(char max_len)
{
    for (i = 0; i != max_len; i++)
        checksum += EPS[i];
    return checksum == 0;
}

static bool check_eps()
{
    while (EPS != reinterpret_cast<char *>(0xFFFFF))
    {
#ifdef i386
        if (Str_Int::same<char>(EPS,"_SM_",bit32_size))
            if (chksum(EPS[4])) break;
#endif
        if (Str_Int::same<char>(EPS,"_SM3_",bit64_size))
            if (chksum(EPS[5])) break;
        EPS += 16;
    }
    if (reinterpret_cast<unsigned>(EPS) == 0x100000)
        return false;
    else
        return true;
}