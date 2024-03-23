// 2024/03/23 14:44:40 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines_win.h"
#include "GUI/Dialogs/TransmitterDialog.h"
#include "Settings/Settings.h"
#include "Modules/CMT2210AW/EmulatorReceiver.h"


TransmitterDialog *TransmitterDialog::self = nullptr;


TransmitterDialog::TransmitterDialog(wxWindow *parent) : wxDialog(nullptr, wxID_ANY, _("Передатчик"))
{
    wxSize client_size{ 130, 220 };

    SetMinClientSize(client_size);
    SetClientSize(client_size);

    pchar names[Source::Count] =
    {
        "Звонок",
        "Мобильный",
        "Телефон",
        "Домофон",
        "Датчик"
    };


    for (int i = 0; i < Source::Count; i++)
    {
        new wxButton(this, ID_BUTTON_SIGNAL_1 + i, names[i], { 10, 10 + i * 40 }, { 100, 30 });
    }

    Bind(wxEVT_BUTTON, &TransmitterDialog::OnEventButton, this);

    SetPosition( parent->GetPosition() );
}


void TransmitterDialog::Create(wxWindow *parent)
{
    self = new TransmitterDialog(parent);
}


void TransmitterDialog::Delete()
{
    delete self;
}


void TransmitterDialog::OnEventButton(wxCommandEvent &event)
{
    EmuRecv::EmulateSignal((Source::E)(event.GetId() - ID_BUTTON_SIGNAL_1));

    event.Skip();
}
