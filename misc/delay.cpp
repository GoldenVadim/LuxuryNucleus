#include <drivers/rtc/cmos.hpp>
#include "delay.hpp"
using namespace Library;

void Utilities::delay(unsigned s)
{
    unsigned elapsed, rtc_sec = Drivers::CMOS::get_bcd_seconds();

    for (elapsed = 0; elapsed != s; ++elapsed)
    {
        while (rtc_sec == Drivers::CMOS::get_bcd_seconds())
        {}
        rtc_sec = Drivers::CMOS::get_bcd_seconds();
    }
}