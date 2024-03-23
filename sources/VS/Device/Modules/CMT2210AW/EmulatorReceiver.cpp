// 2024/03/15 15:54:34 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Modules/CMT2210AW/EmulatorReceiver.h"
#include <cstdlib>


namespace EmuRecv
{
    static const uint codes[Source::Count] = { 0x7E9E, 0x7EA6, 1, 2, 3 };

    static uint code = 0;
}


uint EmuRecv::NextPacket()
{
    uint result = code;

    code = 0;

    return result;
}


void EmuRecv::EmulateSignal(Source::E source)
{
    code = codes[source];
}
