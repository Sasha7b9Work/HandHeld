// 2024/03/20 20:05:13 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Modules/PCF8563/PCF8563.h"


struct Record
{
    uint         crc;            // Если здесь ноль, то запись стёрта
    RTCDateTime  time;
    uint8        source;         // В старшем бите - 1/0 - принято/непринято
    uint8        control_bits;   // Сюда записываем ноль, чтобы убедиться, что запись прошла успешно. Не участвует в вычислении CRC
    uint         CalculateCRC() const;
    const uint8 *Begin() const;
    const uint8 *End() const;
    bool         IsEmpty() const;
};


// Здесь будут храниться принятые и непринятые вызовы
namespace Storage
{
    void Init();

    void Append(const Record &);

    int GetCountRecords();

    Record Get(int);
}
