// 2024/03/06 14:37:43 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Modules/PCF8563/PCF8563.h"


namespace PCF8563
{
    static RTCDateTime time =
    {
        6,
        5,
        4,
        1,
        2,
        3,
        0
    };
}


void PCF8563::Init()
{

}


void PCF8563::Update()
{

}


void PCF8563::SetTimer(uint /*time_sec*/)
{

}


void PCF8563::GetDateTime(RTCDateTime *date_time)
{
    *date_time = time;
}


void PCF8563::SetDateTime(RTCDateTime *date_time)
{
    time = *date_time;
}
