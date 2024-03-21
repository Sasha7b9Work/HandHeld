// 2024/03/20 20:05:55 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Storage/Storage.h"
#include "Settings/Settings.h"


void Storage::Init()
{

}


void Storage::Append(const Record &)
{

}


int Storage::GetCountRecords()
{
    return 10;
}


Record Storage::Get(int num)
{
    Record result =
    {
        { 0, 0, 0, 0, 0, 0, 0 },
        (uint8)(num % Source::Count)
    };

    if (num % 2)
    {
        result.source |= 0x80;
    }

    return result;
}
