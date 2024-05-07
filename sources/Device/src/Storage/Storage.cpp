// 2024/05/07 08:31:57 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines_win.h"
#include "Storage/Storage.h"
#include "Hardware/HAL/HAL.h"


namespace Storage
{
    // —только байт отводитс€ дл€ хранени€ одной записи
    static const uint BYTES_FOR_RECORD = 64;

    struct Page
    {
        Page(int _number) : number(_number) { }

        int GetCountRecords() const
        {
            int result = 0;

            for (uint address = Begin(); address < End(); address += BYTES_FOR_RECORD)
            {
                Record *record = (Record *)address;

                if (record->crc != (uint)(-1))
                {
                    result++;
                }
            }

            return result;
        }

        uint Begin() const
        {
            return HAL_ROM::ADDRESS_BEGIN + HAL_ROM::SIZE_PAGE * number;
        }

        uint End() const
        {
            return Begin() + HAL_ROM::SIZE_PAGE;
        }

        Record *GetRecord(int num_record)
        {
            uint address = Begin();

            address += num_record * BYTES_FOR_RECORD;

            return (Record *)address;
        }

        Record *GetFirstEmpty()
        {
            uint address = Begin();

            for (; address < End(); address += BYTES_FOR_RECORD)
            {
                Record *record = (Record *)address;

                if (record->crc == (uint)(-1))
                {
                    break;
                }
            }

            return (address < End()) ? ((Record *)address) : nullptr;
        }

        static Page *GetFirst();
        {
            Page *first = nullptr;

            int count_0 = pages[0]->GetCountRecords();
            int count_1 = pages[1]->GetCountRecords();

            if (count_0 && count_1)
            {
                if (pages[0]->GetRecord(0)->number < pages[1]->GetRecord(0)->number)
                {
                    first = pages[0];
                    second = pages[1];
                }
            }
            else if (count_0 == 0 && count_1 == 0)
            {

            }
            else if (count_0)
            {
                first = pages[0];
            }
            else if (count_1)
            {
                first = pages[1];
            }

            return first;
        }

    private:
        int number;
    };

    static Page page_0(HAL_ROM::PAGE_FIRST_JOURNAL);
    static Page page_1(HAL_ROM::PAGE_SECOND_JOURNAL);

    static Page *pages[2] = { &page_0, &page_1 };

    Page *Page::GetFirst()
    {

    }
}


void Storage::Append(const RTCDateTime &time, Source::E source, bool receive)
{
    Record record =
    {
        0,
        0,
        time,
        (uint8)source,
        0
    };

    if (GetCountRecords() == 0)
    {
        record.number = 1;
    }
    else
    {
        record.number = Storage::Get(GetCountRecords() - 1)->number + 1;
    }

    if (receive)
    {
        record.source |= 0x80;
    }


}


int Storage::GetCountRecords()
{
    int result = 0;

    for (int page = 0; page < 2; page++)
    {
        result += pages[page]->GetCountRecords();
    }

    return result;;
}


Record *Storage::Get(int number)
{
    if (number >= GetCountRecords())
    {
        return nullptr;
    }

    Page *first = nullptr;
    Page *second = nullptr;

    int count_0 = pages[0]->GetCountRecords();
    int count_1 = pages[1]->GetCountRecords();

    if (count_0 && count_1)
    {
        if (pages[0]->GetRecord(0)->number < pages[1]->GetRecord(0)->number)
        {
            first = pages[0];
            second = pages[1];
        }
    }
    else if (count_0 == 0 && count_1 == 0)
    {

    }
    else if (count_0)
    {
        first = pages[0];
    }
    else if (count_1)
    {
        first = pages[1];
    }

    if (number < HAL_ROM::SIZE_PAGE / BYTES_FOR_RECORD)
    {
        return first->GetRecord(number);
    }

    number -= HAL_ROM::SIZE_PAGE / BYTES_FOR_RECORD;

    return second->GetRecord(number);
}
