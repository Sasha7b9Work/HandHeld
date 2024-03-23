// 2024/03/15 15:54:34 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Modules/CMT2210AW/EmulatorReceiver.h"
#include <cstdlib>


namespace EmuRecv
{
    static const uint64 words[3] =
    {
        0x1c5b8b716e,
        0x2dc5b8b0e9e2c3a4,
        0x748e9e2dc5874f16
    };


    static bool GetBit(int);

    static int current_bit = 0;
}


bool EmuRecv::NextBit()
{
    if (current_bit > 1000)
    {
        current_bit = std::rand() % 1000;
    }

    return GetBit(current_bit++);
}


bool EmuRecv::GetBit(int num_bit)
{
    while (num_bit > 164)
    {
        num_bit -= 165;
    }

    int index = 0;
    if (num_bit < 37)
    {
        num_bit = 36 - num_bit;
        index = 0;
    }
    else if (num_bit < 101)
    {
        num_bit = 63 - (num_bit - 37);
        index = 1;
    }
    else
    {
        num_bit = 63 - (num_bit - 37 - 64);
        index = 2;
    }

    return (words[index] & (((uint64)1) << num_bit)) != 0;
}
