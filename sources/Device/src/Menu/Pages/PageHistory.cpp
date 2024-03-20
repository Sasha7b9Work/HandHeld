// 2024/03/07 09:45:23 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Menu/MenuItemDef.h"
#include "Display/Display.h"
#include "Storage/Storage.h"


namespace PageHistory
{
    static int top_record = 0;

    static void DrawRecord(int x, int y, int num_record)
    {
        if (num_record >= Storage::GetCountRecords())
        {
            return;
        }

        Text<>("%d/%d", num_record + 1, Storage::GetCountRecords()).Write(x, y, Color::WHITE);

        const Record rec = Storage::Get(num_record);
        const RTCDateTime time = rec.time;

        Text<>("%02d/%02d/%02d %02d:%02d:%02d",
            time.Day, time.Month, time.Year, time.Hour, time.Minute, time.Second).Write(x + 5, y + 12);

        Rect(10, 10).Draw(x + 120, y + 10);
    }

    static void FuncDraw_History()
    {
        HLine(160).Draw(0, 26, Color::WHITE);
        HLine(160).Draw(0, 53);

        const int num_records = Storage::GetCountRecords();

        if (num_records > 0)
        {
            DrawRecord(0, 0, top_record);

            if (num_records > 1)
            {
                DrawRecord(0, 28, (top_record + 1) % Storage::GetCountRecords());

                if (num_records > 2)
                {
                    DrawRecord(0, 55, (top_record + 2) % Storage::GetCountRecords());
                }
            }
        }
    }

    static bool Func_ActionKey(const Action &action)
    {
        if (action.key == Key::Menu || action.key == Key::Cancel)
        {
            return false;
        }
        else if (action.key == Key::Up)
        {
            top_record--;
        }
        else if (action.key == Key::Down)
        {
            top_record++;
        }

        if (top_record < 0)
        {
            top_record = Storage::GetCountRecords() - 1;
        }
        else if (top_record >= Storage::GetCountRecords())
        {
            top_record = 0;
        }

        return true;
    }

    static void FuncDraw_Closed()
    {
        Font::SetSize(2);

        Text<>("%d ÂÛÇÎÂÎÂ", Storage::GetCountRecords()).Write(10, 35, Color::WHITE);

        Font::SetSize(1);
    }

    DEF_PAGE_0(pageHistory, PageMain::self, "ÆÓÐÍÀË ÂÛÇÎÂÎÂ",
        FuncDraw_Closed,
        FuncDraw_History,
        Func_ActionKey
    );

    const Item *const self = &pageHistory;
}
