// 2024/03/23 17:03:03 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Settings/Settings.h"


// ������� ������ ������, ��� ������ � �������
struct Queue
{
    // �������� � �����
    void Push(Source::E)
    {

    }

    // ������� �� ������
    void Pop()
    {

    }

    int Size() const
    {
        return pointer;
    }

    bool IsEmpty() const
    {
        return Size() == 0;
    }

private:

    Source::E buffer[Source::Count] = { Source::Count, Source::Count, Source::Count, Source::Count, Source::Count };
    int pointer = 0;
};
