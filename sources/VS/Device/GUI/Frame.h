// 2022/04/27 11:12:04 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Hardware/Timer.h"
#define WIN32_LEAN_AND_MEAN
#include "wx/wx.h"


class Frame : public wxFrame
{
public:
    Frame(const wxString &title);

    static Frame *Self() { return self; };

    void OnTimer(wxTimerEvent &);

    void BeginScene();

    void EndScene();

private:

    wxTimer timer;
    static Frame *self;

    TimeMeterMS meterButton;        // Для кнопки
    wxTimer timerButton;
};
