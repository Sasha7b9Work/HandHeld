// 2024/03/23 14:44:32 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class TransmitterDialog : public wxDialog
{
public:

    static TransmitterDialog *self;

    static void Create();

    static void Delete();

private:

    TransmitterDialog();
};
