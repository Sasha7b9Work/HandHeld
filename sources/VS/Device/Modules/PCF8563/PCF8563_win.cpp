// 2024/03/06 14:37:43 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Modules/PCF8563/PCF8563.h"


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
    date_time->Hour = 1;
    date_time->Minute = 2;
    date_time->Second = 3;
    date_time->Day = 4;
    date_time->Month = 5;
    date_time->Year = 2006;
}
