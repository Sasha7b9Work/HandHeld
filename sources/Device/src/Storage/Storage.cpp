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

        Page(int i) : num_page(i)
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

        // Последняя запись с существующими данными
        Record *LastExistRecord()
        {
            Record *record = LastRecord() - 1;

            while (record >= FirstRecord())
            {
                if (record->IsValidData())
                {
                    return record;
                }

                record++;
            }

            return nullptr;
        }

        void Erase()
        {
            HAL_ROM::ErasePage(num_page);
        }

        void Write(const Record &record)
        {
            Record *place = FirstRecord();
            Record *last = LastRecord();

            while (place < last)
            {
                if (place->IsEmpty())
                {
                    HAL_ROM::WriteBuffer((uint)place, &record, sizeof(record));
                    break;
                }
            }
        }

        int GetCountRecords()
        {
            return 0;

            Record *place = FirstRecord();
            Record *last = LastRecord();

            int result = 0;

            while(place < last)
            {
                if (place->IsValidData())
                {
                    result++;
                }

                place++;
            }

            return result;
        }

        static Page FromEnd(int index)
        {
            return Page(HAL_ROM::PAGE_LAST_JOURNAL - index);
        }

        // Столько всего страниц
        static int Count()
        {
            return HAL_ROM::PAGE_LAST_JOURNAL - HAL_ROM::PAGE_FIRST_JOURNAL;
        }

    private:
        int num_page;
        uint address;
    };
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

    Record last_record =
    {
        0, { 0, 0, 0, 0, 0, 0 }, 0, 0
    };

    int num_page = 0;

    for (int i = HAL_ROM::PAGE_FIRST_JOURNAL; i < HAL_ROM::PAGE_LAST_JOURNAL; i++)
    {
        Page page(i);

        Record *record = page.LastExistRecord();

        if (!record)
        {
            num_page = i;
            break;
        }

        if (record->time < last_record.time)
        {
            last_record = *record;
            num_page = i;
        }
    }

    Page page(num_page);

    page.Erase();

    Record record = rec;
    record.crc = rec.CalculateCRC();
    record.control_bits = 0;

    page.Write(record);
}


int Storage::GetCountRecords()
{
    int result = 0;

    for (int i = 0; i < Page::Count(); i++)
    {
        result += Page::FromEnd(i).GetCountRecords();
    }

    return result;
}


Record Storage::Get(int /*num*/)
{
    return Record();

//  for (int i = 0; i < Page::Count(); i++)
//    {
//        Page page(i);
//
//        if (num < page.GetCountRecords())
//        {
//            page.GetRecord(num);
//        }
//
//        num -= page.GetCountRecords();
//
//        if (num < 0)
//        {
//            break;
//        }
//    }
//
//    Record record =
//    {
//
//    }
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


bool Record::IsValidData() const
{
    return control_bits == 0 && crc == CalculateCRC();
}
