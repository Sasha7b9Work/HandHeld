// 2024/03/01 22:46:05 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Modules/CMT2210AW/CMT2210AW.h"
#include "Hardware/HAL/HAL_PINS.h"
#include "Display/Display.h"
#include "Settings/Settings.h"
#include "Modules/CMT2210AW/EmulatorReceiver.h"
#include <gd32e23x.h>


namespace CMT2210AW
{
    struct ReceivedData
    {
        ReceivedData()
        {
            for (int i = 0; i < 15; i++)
            {
                values[i] = 0;
            }
        }
        int values[15];
    };


    struct Data
    {
        uint64 words[3] = { 0, 0, 0 };
        uint64 xors[3] = { 0, 0, 0 };

        void Reset();

        void AppendBit(bool);

        void VerifyPreambule1();

        void VerifyPreambule2();

        void VerifyPreambule3();

        uint GetOnes(uint64);

        bool GetBit(int num_bit) const;

        void Log();
    };

    static Data data;
}


void CMT2210AW::Init()
{
    pinDOUT.Init();
}


void CMT2210AW::CallbackOnBit()
{
    data.AppendBit(pinDOUT.IsHi());
}


void CMT2210AW::Data::AppendBit(bool bit)
{
    words[0] <<= 1;

    if (words[1] & 0x8000000000000000)
    {
        words[0] |= 1;
    }

    words[1] <<= 1;

    if (words[2] & 0x8000000000000000)
    {
        words[1] |= 1;
    }

    words[2] <<= 1;

//    if (EmuRecv::NextBit())
    if (bit)
    {
        words[2] |= 1;
    }

    // ѕосылка будет вот така€ : 111111010001101 - 15 бит,
    // где кажда€ единица - это пр€ма€ последовательность баркера(11100010110),
    // а ноль - инверсна€(00011101001)
    // 0x1c5b8b716e 0x2dc5b8b0e9e2c3a4 0x748e9e2dc5874f16

    words[0] &= 0x1fffffffff;               // «десь оставл€ем только 165 - 64 - 64 = 37 бит

    xors[0] = words[0] ^ 0x0000001c5b8b716e;
    xors[1] = words[1] ^ 0x2dc5b8b0e9e2c3a4;
    xors[2] = words[2] ^ 0x748e9e2dc5874f16;

    VerifyPreambule3();
}


void CMT2210AW::Data::VerifyPreambule2()
{
    ReceivedData r_data;

    for (int i = 0; i < 15; i++)
    {
        for (int bit = 0; bit < 11; bit++)
        {
            if (!GetBit(i * 11 + bit))
            {
                r_data.values[i]++;
            }
        }

        if (r_data.values[i] < 8)
        {
            return;
        }
        else
        {
            if (i == 4)
            {
                Log();
            }
        }
    }

    Source::Receive(Source::DoorBell);
}


void CMT2210AW::Data::Log()
{
    char buffer[165];

    for (int i = 0; i < 165; i++)
    {
        buffer[i] = GetBit(i) ? 1 : 0;
    }

    char *pointer = buffer;
    pointer = pointer;
}


uint CMT2210AW::Data::GetOnes(uint64 bit)
{
    uint result = 0;

    for (uint64 i = 0; i < 11; i++)
    {
        if ((bit & (((uint64)1) << i)) != 0)
        {
            result++;
        }
    }

    return result;
}


void CMT2210AW::Data::VerifyPreambule3()
{
#define BARKERTRESHOLD 3

    uint packet = 0;

    //check out HEAD
    if ((GetOnes((xors[0] >> 26) & 0x07FF) < BARKERTRESHOLD) &&
        (GetOnes((xors[0] >> 15) & 0x07FF) < BARKERTRESHOLD) &&
        (GetOnes((xors[0] >> 4) & 0x07FF) < BARKERTRESHOLD) &&
        ((GetOnes(xors[0] & 0x0F) + (GetOnes((xors[1] >> 57) & 0x07FF))) < BARKERTRESHOLD) &&
        (GetOnes((xors[1] >> 46) & 0x07FF) < BARKERTRESHOLD) &&
        (GetOnes((xors[1] >> 35) & 0x07FF) < BARKERTRESHOLD) &&
        (GetOnes((xors[1] >> 24) & 0x07FF) > (11 - BARKERTRESHOLD))
        )
    {
        //HEAD 1111110 received, now need to check out PAYLOAD
        uint32_t bitlevel = 0;

        //check bit 0
        bitlevel = GetOnes(xors[2] & 0x07FF);
        if (bitlevel < BARKERTRESHOLD)
            packet |= 0x0001;
        else
            if (bitlevel < (11 - BARKERTRESHOLD))
                return;

        //check bit 1
        bitlevel = GetOnes((uint16_t)((xors[2] >> 11) & 0x07FF));
        if (bitlevel < BARKERTRESHOLD)
            packet |= 0x0002;
        else
            if (bitlevel < (11 - BARKERTRESHOLD))
                return;

        //check bit 2
        bitlevel = GetOnes((uint16_t)((xors[2] >> 22) & 0x07FF));
        if (bitlevel < BARKERTRESHOLD)
            packet |= 0x0004;
        else
            if (bitlevel < (11 - BARKERTRESHOLD))
                return;

        //check bit 3
        bitlevel = GetOnes((uint16_t)((xors[2] >> 33) & 0x07FF));
        if (bitlevel < BARKERTRESHOLD)
            packet |= 0x0008;
        else
            if (bitlevel < (11 - BARKERTRESHOLD))
                return;

        //check bit 4
        bitlevel = GetOnes((uint16_t)((xors[2] >> 44) & 0x07FF));
        if (bitlevel < BARKERTRESHOLD)
            packet |= 0x0010;
        else
            if (bitlevel < (11 - BARKERTRESHOLD))
                return;

        //check bit 5
        bitlevel = (uint)(GetOnes((uint16_t)((xors[2] >> 55) & 0x07FF)) + GetOnes((uint16_t)(xors[1] & 0x03)));
        if (bitlevel < BARKERTRESHOLD)
            packet |= 0x0020;
        else
            if (bitlevel < (11 - BARKERTRESHOLD))
                return;

        //check bit 6
        bitlevel = GetOnes((uint16_t)((xors[1] >> 2) & 0x07FF));
        if (bitlevel < BARKERTRESHOLD)
            packet |= 0x0040;
        else
            if (bitlevel < (11 - BARKERTRESHOLD))
                return;

        //check bit 7
        bitlevel = GetOnes((uint16_t)((xors[1] >> 13) & 0x07FF));
        if (bitlevel < BARKERTRESHOLD)
            packet |= 0x0080;
        else
            if (bitlevel < (11 - BARKERTRESHOLD))
                return;

        if (packet == 0x8D)
        {
            Source::Receive(Source::DoorBell);
        }
    }
}


void CMT2210AW::Data::VerifyPreambule1()
{
#define BARKERTRESHOLD 3

static const uint8_t BITSSETTABLEFF[2048] =
{
    0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8,

    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8,
    4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8, 5, 6, 6, 7, 6, 7, 7, 8, 6, 7, 7, 8, 7, 8, 8, 9,

    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8,
    4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8, 5, 6, 6, 7, 6, 7, 7, 8, 6, 7, 7, 8, 7, 8, 8, 9,

    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8,
    4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8, 5, 6, 6, 7, 6, 7, 7, 8, 6, 7, 7, 8, 7, 8, 8, 9,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8,
    4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8, 5, 6, 6, 7, 6, 7, 7, 8, 6, 7, 7, 8, 7, 8, 8, 9,
    4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8, 5, 6, 6, 7, 6, 7, 7, 8, 6, 7, 7, 8, 7, 8, 8, 9,
    5, 6, 6, 7, 6, 7, 7, 8, 6, 7, 7, 8, 7, 8, 8, 9, 6, 7, 7, 8, 7, 8, 8, 9, 7, 8, 8, 9, 8, 9, 9,10,

    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8,
    4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8, 5, 6, 6, 7, 6, 7, 7, 8, 6, 7, 7, 8, 7, 8, 8, 9,

    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8,
    4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8, 5, 6, 6, 7, 6, 7, 7, 8, 6, 7, 7, 8, 7, 8, 8, 9,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8,
    4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8, 5, 6, 6, 7, 6, 7, 7, 8, 6, 7, 7, 8, 7, 8, 8, 9,
    4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8, 5, 6, 6, 7, 6, 7, 7, 8, 6, 7, 7, 8, 7, 8, 8, 9,
    5, 6, 6, 7, 6, 7, 7, 8, 6, 7, 7, 8, 7, 8, 8, 9, 6, 7, 7, 8, 7, 8, 8, 9, 7, 8, 8, 9, 8, 9, 9,10,

    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8,
    4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8, 5, 6, 6, 7, 6, 7, 7, 8, 6, 7, 7, 8, 7, 8, 8, 9,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8,
    4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8, 5, 6, 6, 7, 6, 7, 7, 8, 6, 7, 7, 8, 7, 8, 8, 9,
    4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8, 5, 6, 6, 7, 6, 7, 7, 8, 6, 7, 7, 8, 7, 8, 8, 9,
    5, 6, 6, 7, 6, 7, 7, 8, 6, 7, 7, 8, 7, 8, 8, 9, 6, 7, 7, 8, 7, 8, 8, 9, 7, 8, 8, 9, 8, 9, 9,10,

    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8,
    4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8, 5, 6, 6, 7, 6, 7, 7, 8, 6, 7, 7, 8, 7, 8, 8, 9,
    4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8, 5, 6, 6, 7, 6, 7, 7, 8, 6, 7, 7, 8, 7, 8, 8, 9,
    5, 6, 6, 7, 6, 7, 7, 8, 6, 7, 7, 8, 7, 8, 8, 9, 6, 7, 7, 8, 7, 8, 8, 9, 7, 8, 8, 9, 8, 9, 9,10,
    4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8, 5, 6, 6, 7, 6, 7, 7, 8, 6, 7, 7, 8, 7, 8, 8, 9,
    5, 6, 6, 7, 6, 7, 7, 8, 6, 7, 7, 8, 7, 8, 8, 9, 6, 7, 7, 8, 7, 8, 8, 9, 7, 8, 8, 9, 8, 9, 9,10,
    5, 6, 6, 7, 6, 7, 7, 8, 6, 7, 7, 8, 7, 8, 8, 9, 6, 7, 7, 8, 7, 8, 8, 9, 7, 8, 8, 9, 8, 9, 9,10,
    6, 7, 7, 8, 7, 8, 8, 9, 7, 8, 8, 9, 8, 9, 9,10, 7, 8, 8, 9, 8, 9, 9,10, 8, 9, 9,10, 9,10,10,11
};

    uint packet = 0;

    //check out HEAD
    if((BITSSETTABLEFF[(xors[0] >> 26) & 0x07FF] < BARKERTRESHOLD) &&
       (BITSSETTABLEFF[(xors[0] >> 15) & 0x07FF] < BARKERTRESHOLD) &&
       (BITSSETTABLEFF[(xors[0] >>  4) & 0x07FF] < BARKERTRESHOLD) &&
       ((BITSSETTABLEFF[xors[0] & 0x0F] + (BITSSETTABLEFF[(xors[1] >> 57) & 0x07FF])) < BARKERTRESHOLD) &&
       (BITSSETTABLEFF[(xors[1] >> 46) & 0x07FF] < BARKERTRESHOLD) &&
       (BITSSETTABLEFF[(xors[1] >> 35) & 0x07FF] < BARKERTRESHOLD) &&
       (BITSSETTABLEFF[(xors[1] >> 24) & 0x07FF] > (11 - BARKERTRESHOLD))
      )
    {
        //HEAD 1111110 received, now need to check out PAYLOAD
        uint32_t bitlevel = 0;

        //check bit 0
        bitlevel = BITSSETTABLEFF[(uint16_t)xors[2] & 0x07FF];
        if(bitlevel < BARKERTRESHOLD)
            packet |= 0x0001;
        else
            if(bitlevel < (11 - BARKERTRESHOLD))
                return;

        //check bit 1
        bitlevel = BITSSETTABLEFF[(uint16_t)((xors[2] >> 11) & 0x07FF)];
        if(bitlevel < BARKERTRESHOLD)
            packet |= 0x0002;
        else
            if(bitlevel < (11 - BARKERTRESHOLD))
                return;

        //check bit 2
        bitlevel = BITSSETTABLEFF[(uint16_t)((xors[2] >> 22) & 0x07FF)];
        if(bitlevel < BARKERTRESHOLD)
            packet |= 0x0004;
        else
            if(bitlevel < (11 - BARKERTRESHOLD))
                return;

        //check bit 3
        bitlevel = BITSSETTABLEFF[(uint16_t)((xors[2] >> 33) & 0x07FF)];
        if(bitlevel < BARKERTRESHOLD)
            packet |= 0x0008;
        else
            if(bitlevel < (11 - BARKERTRESHOLD))
                return;

        //check bit 4
        bitlevel = BITSSETTABLEFF[(uint16_t)((xors[2] >> 44) & 0x07FF)];
        if(bitlevel < BARKERTRESHOLD)
            packet |= 0x0010;
        else
            if(bitlevel < (11 - BARKERTRESHOLD))
                return;

        //check bit 5
        bitlevel = (uint)(BITSSETTABLEFF[(uint16_t)((xors[2] >> 55) & 0x07FF)] + BITSSETTABLEFF[(uint16_t)(xors[1] & 0x03)]);
        if(bitlevel < BARKERTRESHOLD)
            packet |= 0x0020;
        else
            if(bitlevel < (11 - BARKERTRESHOLD))
                return;

        //check bit 6
        bitlevel = BITSSETTABLEFF[(uint16_t)((xors[1] >> 2) & 0x07FF)];
        if(bitlevel < BARKERTRESHOLD)
            packet |= 0x0040;
        else
            if(bitlevel < (11 - BARKERTRESHOLD))
                return;

        //check bit 7
        bitlevel = BITSSETTABLEFF[(uint16_t)((xors[1] >> 13) & 0x07FF)];
        if(bitlevel < BARKERTRESHOLD)
            packet |= 0x0080;
        else
            if(bitlevel < (11 - BARKERTRESHOLD))
                return;

        if (packet == 0x8D)
        {
            Source::Receive(Source::DoorBell);
        }
    }
}


bool CMT2210AW::Data::GetBit(int num_bit) const
{
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

    return (xors[index] & (((uint64)1) << num_bit)) != 0;
}


void CMT2210AW::Data::Reset()
{
    words[0] = xors[0] = 0;
    words[1] = xors[1] = 0;
    words[2] = xors[2] = 0;
}
