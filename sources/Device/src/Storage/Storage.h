// 2024/03/20 20:05:13 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Modules/PCF8563/PCF8563.h"


struct Record
{
    RTCDateTime time;
    uint8       source;     // В старшем бите - 1/0 - принято/непринято
};


// Здесь будут храниться принятые и непринятые вызовы
namespace Storage
{
    void Init();

    void Append(const Record &);

    int GetCountRecords();

    Record Get(int);
}
