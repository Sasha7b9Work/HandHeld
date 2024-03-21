// 2024/03/07 09:45:23 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Menu/MenuItemDef.h"
#include "Display/Display.h"
#include "Storage/Storage.h"


namespace PageHistory
{
    static int top_record = 0;

    static void DrawRecord()
    {
        if (top_record >= Storage::GetCountRecords())
        {
            return;
        }

        int x = 0;
        int y = 0;

        Text<>("%d/%d", top_record + 1, Storage::GetCountRecords()).Write(x, y, Color::WHITE);

        const Record rec = Storage::Get(top_record);
        const RTCDateTime time = rec.time;

        Text<>("%02d/%02d/%02d %02d:%02d:%02d",
            time.Day, time.Month, time.Year, time.Hour, time.Minute, time.Second).Write(x + 5, y + 12);

        Rect(10, 10).Draw(x + 120, y + 10);
    }

    static void FuncDraw_History()
    {
        if (Storage::GetCountRecords() > 0)
        {
            DrawRecord();
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

        Text<>("%d �������", Storage::GetCountRecords()).Write(10, 35, Color::WHITE);

        Font::SetSize(1);
    }

    DEF_PAGE_0(pageHistory, PageMain::self, "������ �������",
        FuncDraw_Closed,
        FuncDraw_History,
        Func_ActionKey
    );

    const Item *const self = &pageHistory;
}
