// 2022/04/27 11:12:04 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Hardware/Timer.h"



class Frame : public wxFrame
{
public:
    Frame(const wxString &title);

    static Frame *Self() { return self; };

    void OnTimer(wxTimerEvent &);

private:

    wxTimer timer;
    static Frame *self;

    TimeMeterMS meterButton;        // Для кнопки
    wxTimer timerButton;

    void OnMouseEvent(wxMouseEvent &);

    void CreateMenu();
};
