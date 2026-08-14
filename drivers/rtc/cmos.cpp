#include <memory/ports.hpp>
#include <misc/str_int.hpp>
#include <memory/alloc.hpp>
#include "register.hpp"
#include "cmos.hpp"
using namespace Miscellaneous;
using namespace Drivers;
using namespace Memory;

unsigned short CMOS::pmio_cmos_index_register = 0x70,
               CMOS::pmio_cmos_data_register = 0x71;

enum
{
    seconds_reg = 0,
    minutes_reg = 0x2,
    hours_reg = 0x4
};

static char rtc_reg_get(const char &reg)
{
    Ports::write(CMOS::pmio_cmos_index_register,reg);
    return Ports::read(CMOS::pmio_cmos_data_register);
}

char CMOS::get_bcd_seconds()
{
    return rtc_reg_get(seconds_reg);
}

char CMOS::get_bcd_minutes()
{
    return rtc_reg_get(minutes_reg);
}

char CMOS::get_bcd_hours()
{
    return rtc_reg_get(hours_reg);
}

char CMOS::get_seconds()
{
    return Str_Int::bcd_to_bin(get_bcd_seconds());
}

char CMOS::get_minutes()
{
    return Str_Int::bcd_to_bin(get_bcd_minutes());
}

char CMOS::get_hours()
{
    return Str_Int::bcd_to_bin(get_bcd_hours());
}

static char HHMMSS[9] {'0','0',':','0','0',':','0','0'};

char *CMOS::get_HHMMSS_str()
{ // HH:MM:SS
  // 01234567
    char hh = get_hours(), mm = get_minutes(), ss = get_seconds();
    
    Memory::copy_to<char>(HHMMSS,Str_Int::to_string(hh,10,2),2);
    Memory::copy_to<char>(&HHMMSS[3],Str_Int::to_string(mm,10,2),2);
    Memory::copy_to<char>(&HHMMSS[6],Str_Int::to_string(ss,10,2),2);

    return HHMMSS;
}