// 2024/03/20 20:05:55 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Storage/Storage.h"
#include "Settings/Settings.h"
#include "Utils/Math.h"
#include "Hardware/HAL/HAL.h"


namespace Storage
{
    struct Page
    {
        static const int RECORS_ON_PAGE = HAL_ROM::SIZE_PAGE / sizeof(Record);

        Page(int i)
        {
            address = (uint)(HAL_ROM::ADDRESS_BEGIN + (uint)i * HAL_ROM::SIZE_PAGE);
        }

        // Есть ли место для новой записи
        Record *RecordForWrite()
        {
            Record *record = FirstRecord();

            while (record < LastRecord())
            {
                if (record->IsEmpty())
                {
                    return record;
                }

                record++;
            }

            return nullptr;
        }

        Record *FirstRecord()
        {
            return (Record *)address;
        }

        Record *LastRecord()
        {
            return (Record *)(address + RECORS_ON_PAGE * sizeof(Record));
        }

    private:
        uint address;
    };
}


void Storage::Init()
{

}


void Storage::Append(const Record &rec)
{
    for (int i = HAL_ROM::PAGE_FIRST_JOURNAL; i < HAL_ROM::PAGE_LAST_JOURNAL; i++)
    {
        Page page(i);

        Record *place = page.RecordForWrite();

        if (place)
        {
            Record record = rec;
            record.crc = rec.CalculateCRC();
            record.control_bits = 0;

            HAL_ROM::WriteBuffer((uint)place, &record, sizeof(record));

            return;
        }
    }
}


int Storage::GetCountRecords()
{
    return 10;
}


Record Storage::Get(int num)
{
    Record result =
    {
        0,
        { 0, 0, 0, 0, 0, 0 },
        (uint8)(num % Source::Count),
        0
    };

    if (num % 2)
    {
        result.source |= 0x80;
    }

    return result;
}


const uint8 *Record::Begin() const
{
    return (const uint8 *)this;
}


const uint8 *Record::End() const
{
    return Begin() + sizeof(*this);
}


uint Record::CalculateCRC() const
{
    return Math::CalculateCRC(Begin(), &control_bits - Begin());
}


bool Record::IsEmpty() const
{
    const uint8 *pointer = Begin();
    const uint8 *end = End();

    while (pointer < end)
    {
        if (*pointer++ != 0xFF)
        {
            return false;
        }
    }

    return true;
}
