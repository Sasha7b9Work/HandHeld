// 2024/03/23 14:44:40 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines_win.h"
#include "GUI/Dialogs/TransmitterDialog.h"


TransmitterDialog *TransmitterDialog::self = nullptr;


TransmitterDialog::TransmitterDialog() : wxDialog(nullptr, wxID_ANY, _("Передатчик"))
{
    wxSize client_size{ 100, 100 };

    SetMinClientSize(client_size);
    SetClientSize(client_size);
}


void TransmitterDialog::Create()
{
    self = new TransmitterDialog();
}


void TransmitterDialog::Delete()
{
    delete self;
}
