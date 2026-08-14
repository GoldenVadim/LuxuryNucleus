#include <memory/alloc.hpp>
#include "str_int.hpp"
using namespace Miscellaneous;

unsigned long long Str_Int::__sizeof(const char *const &string)
{
    unsigned long long len = 0;
    while (string[len])
        ++len;
    return len;
}

static constexpr char base_num[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
const char* Str_Int::to_string(int integer, const char &base, char additional_offset)
{ // vibecoded, for reason: заебался уже нахуй
    // Handle special case 0 explicitly
    if (integer == 0)
    {
        switch (base)
        {
            case 2:  return "0b0";
            case 8:  return "0o0";
            case 16: return "0x0";
            default: return "0";
        }
    }

    // 1. Safe handling of negative numbers (avoids INT_MIN UB)
    bool negative = (integer < 0);
    unsigned int uinteger = negative ? static_cast<unsigned int>(-static_cast<long long>(integer)) 
                                     : static_cast<unsigned int>(integer);

    // 2. Count required digit count
    unsigned long long digit_count = 0;
    for (unsigned int temp = uinteger; temp != 0; temp /= base)
        ++digit_count;

    // Apply minimum zero-padding if specified
    if (additional_offset > digit_count)
        digit_count = additional_offset;

    // 3. Calculate total buffer size (+ prefix + negative sign + null terminator)
    unsigned long long alloc_size = digit_count + 1; // +1 for '\0'
    if (negative) alloc_size++;
    if (base != 10) alloc_size += 2; // prefix like "0x"

    char* str = Memory::allocate<char>(alloc_size);
    unsigned long long index = 0;

    // 4. Add sign
    if (negative)
        str[index++] = '-';

    // 5. Add base prefix
    if (base != 10)
    {
        str[index++] = '0';
        switch (base)
        {
            case 2:  str[index++] = 'b'; break;
            case 8:  str[index++] = 'o'; break;
            case 16: str[index++] = 'x'; break;
            default: break;
        }
    }

    // 6. Write digits in reverse onto a local stack buffer (no dynamic leak)
    char temp_buf[65]; // Large enough for 64-bit binary digits
    unsigned long long temp_idx = 0;

    while (uinteger != 0)
    {
        temp_buf[temp_idx++] = base_num[uinteger % base];
        uinteger /= base;
    }

    // Pad with leading zeros if additional_offset > actual digits
    while (temp_idx < static_cast<unsigned char>(additional_offset))
    {
        temp_buf[temp_idx++] = '0';
    }

    // Copy digits out in correct order
    while (temp_idx > 0)
    {
        str[index++] = temp_buf[--temp_idx];
    }

    // 7. ALWAYS null-terminate the string
    str[index] = '\0';

    return str;
} ////////////////////////////////////////////

int Str_Int::bcd_to_bin(int bcd)
{
    return (bcd & 0xF) + ((bcd / 16) * 10);
}

bool Str_Int::__equal(const char *const &first, const char *const &second, const unsigned long long &size)
{
    for (unsigned long long _ = 0; _ != size; ++_)
        if (first[_] != second[_])
            return false;
    return true;
}