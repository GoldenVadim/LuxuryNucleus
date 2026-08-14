/*
    textcon: The VT application for using text-based console.
*/

#include "../fonts.hpp"
#include "textcon.hpp"
#include "vt.hpp"
using namespace Graphics;

static unsigned short X = 0, Y = 0, prev_Y;
static bool newlined_at_end = false;

static void scroll()
{
    for (Y = 0; Y != *VT::height;)
    {
        prev_Y = Y++;
        for (X = 0; X != *VT::width; ++X)
            VT::put_entry(VT::get_entry(X, Y), X, prev_Y);
    }
    X = 0;
    --Y;
}

void VT::textcon::put_char(const char &entry)
{
    switch (entry)
    {
        case '\n':
        {
            case_n:
            if (newlined_at_end)
                scroll();
            else if (++Y == *VT::height)
                newlined_at_end = true;
            goto case_r;
        }
        case '\r':
        {
            case_r:
            X = 0;
            break;
        }
        default:
        {
            if (newlined_at_end)
            {
                scroll();
                newlined_at_end = false;
            }
            VT::put_entry(entry, X++, Y);
            if (X == *VT::width)
                goto case_n;
            VT::move_cursor(X, Y);
        }
    }
}

void VT::textcon::print(const char *const &text, const unsigned long long &len)
{
    for (unsigned long long _ = 0; _ != len; ++_)
        put_char(text[_]);
}