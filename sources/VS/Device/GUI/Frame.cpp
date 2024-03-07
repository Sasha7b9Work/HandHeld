// 2022/04/27 11:11:56 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Frame.h"
#include "Display/Display.h"
#include "Modules/ST7735/ST7735.h"
#include "Application.h"
#include "Menu/Menu.h"
#include "wx/statline.h"
#include "Keyboard/Keyboard.h"


namespace Keyboard
{
    void AppendAction(const Action &);
}



// Здесь нарисованная картинка
static wxBitmap bitmap(Display::WIDTH, Display::HEIGHT);

// Здесь будем рисовать
static wxMemoryDC memDC;

Frame *Frame::self = nullptr;

static const int IMAGE_SCALE = 2;

enum
{
    TIMER_ID = 111,
    TIMER_BUTTON_ID
};

class Screen : public wxPanel
{
public:
    Screen(wxWindow *parent) : wxPanel(parent)
    {
        SetMinSize({ Display::WIDTH * IMAGE_SCALE, Display::HEIGHT * IMAGE_SCALE });
        SetDoubleBuffered(true);
        Bind(wxEVT_PAINT, &Screen::OnPaint, this);
    }

    void OnPaint(wxPaintEvent &)
    {
        wxPaintDC dc(this);

        wxImage image = bitmap.ConvertToImage().Rescale(Display::WIDTH * IMAGE_SCALE, Display::HEIGHT * IMAGE_SCALE);

        dc.DrawBitmap(wxBitmap(image), 0, 0);
    }
};


static Screen *screen = nullptr;


Frame::Frame(const wxString &title)
    : wxFrame((wxFrame *)NULL, wxID_ANY, title)
{
    SetIcon(wxICON(sample));

    self = this;

    screen = new Screen(this);

    wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(screen);
    SetSizer(sizer);

    Bind(wxEVT_PAINT, &Frame::OnPaint, this);
    Bind(wxEVT_TIMER, &Frame::OnTimer, this, TIMER_ID);

    timerButton.SetOwner(this, TIMER_BUTTON_ID);
    timer.SetOwner(this, TIMER_ID);

    SetClientSize(Display::WIDTH * IMAGE_SCALE + 180, Display::HEIGHT * IMAGE_SCALE);

    wxTopLevelWindowBase::SetMinSize(GetSize());
    wxTopLevelWindowBase::SetMaxSize(GetSize());

    const int maxWidth = wxSystemSettings::GetMetric(wxSYS_SCREEN_X);
    const int maxHeight = wxSystemSettings::GetMetric(wxSYS_SCREEN_Y);

    int x = (maxWidth - GetSize().x) / 2;
    int y = (maxHeight - GetSize().y) / 2;

    SetPosition({ x, y });

    const wxSize SIZE_BUTTON = { 65, 25 };

    int x1 = 330;
    int x2 = 370;
    int x3 = 420;
    int y1 = 15;
    int y2 = 50;
    int y3 = 90;

    (new wxButton(this, ID_BUTTON_MENU, "Menu", { x1, y2 }, SIZE_BUTTON))->Bind(wxEVT_LEFT_DOWN, &Frame::OnMouseEvent, this);

    (new wxButton(this, ID_BUTTON_CANCEL, "Cancel", { x3, y2 }, SIZE_BUTTON))->Bind(wxEVT_LEFT_DOWN, &Frame::OnMouseEvent, this);

    (new wxButton(this, ID_BUTTON_UP, "Up", { x2, y1 }, SIZE_BUTTON))->Bind(wxEVT_LEFT_DOWN, &Frame::OnMouseEvent, this);

    (new wxButton(this, ID_BUTTON_DOWN, "Down", { x2, y3 }, SIZE_BUTTON))->Bind(wxEVT_LEFT_DOWN, &Frame::OnMouseEvent, this);

    timer.StartOnce(25);
}


void Frame::OnTimer(wxTimerEvent &)
{
    timer.Stop();

    Application::Self()->Update();

    timer.Start(25);
}


void Frame::OnMouseEvent(wxMouseEvent &event)
{
    int id = event.GetId();

    Action action;

    action.type = ActionType::Down;

    if (id == ID_BUTTON_MENU)
    {
        action.key = Key::Menu;
    }
    else if (id == ID_BUTTON_CANCEL)
    {
        action.key = Key::Cancel;
    }
    else if (id == ID_BUTTON_UP)
    {
        action.key = Key::Up;
    }
    else if (id == ID_BUTTON_DOWN)
    {
        action.key = Key::Down;
    }

    Keyboard::AppendAction(action);

    event.Skip();
}


static wxColour ConvertColor(Color::E e)
{
    uint16 value = Color::colors[e];

    float b = (float)BLUE_FROM_COLOR(value);
    float g = (float)GREEN_FROM_COLOR(value);
    float r = (float)RED_FROM_COLOR(value);

    uint8 blue  = (uint8)((b / 31.0f) * 255);
    uint8 green = (uint8)((g / 63.0f) * 255);
    uint8 red   = (uint8)((r / 31.0f) * 255);

    return wxColour(red, green, blue);
}


void ST7735::Init()
{

}


void ST7735::WriteBuffer(int y0)
{
    static const wxColour colors[Color::Count] =
    {
        ConvertColor((Color::E)0),
        ConvertColor((Color::E)1),
        ConvertColor((Color::E)2),
        ConvertColor((Color::E)3),
        ConvertColor((Color::E)4),
        ConvertColor((Color::E)5),
        ConvertColor((Color::E)6),
        ConvertColor((Color::E)7),
        ConvertColor((Color::E)8),
        ConvertColor((Color::E)9)
    };

    memDC.SelectObject(bitmap);

    static wxPen pen = *wxWHITE_PEN;

    int line = 0;

    for (int y = y0; y < y0 + Display::HEIGHT / Display::NUMBER_PARTS_HEIGHT; y++)
    {
        uint8 *points = Display::Buffer::GetLine(line++);

        uint8 value = *points;

        for (int x = 0; x < Display::WIDTH; x++)
        {
            pen.SetColour(colors[value]);

            memDC.SetPen(pen);

            memDC.DrawPoint(x + 1, y);

            value = *(++points);
        }
    }

    memDC.SelectObject(wxNullBitmap);

    screen->Refresh();
}
