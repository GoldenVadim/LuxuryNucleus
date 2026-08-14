#include <drivers/rtc/register.hpp>
#include <memory/ports.hpp>
#include "nmi.hpp"
using namespace Drivers;
using namespace Memory;

void Interrupt::NMI::enable()
{
    Ports::write(CMOS::pmio_cmos_index_register, Ports::read(CMOS::pmio_cmos_index_register) & 0x7F);
    Ports::read(CMOS::pmio_cmos_data_register);
}

void Interrupt::NMI::disable()
{
    Ports::write(CMOS::pmio_cmos_index_register, Ports::read(CMOS::pmio_cmos_index_register) | 0x80);
    Ports::read(CMOS::pmio_cmos_data_register);
}