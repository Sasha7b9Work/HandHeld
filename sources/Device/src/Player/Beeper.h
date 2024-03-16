// 2024/03/03 17:06:14 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace Beeper
{
    void Init();

    void Beep();

    // ���������� �������, ����� ����� ������� �������� (�� StartMelody()). ����� �������������� ��� ��������� �������/���.
    void StartMelody();

    // ����� �������
    void OutputSample(uint8);

    // ���������� �������������� ����� ���������� ������� (�� TimerFunc(), ���������� ���������).
    // ����� �������������� ��� ��������� �������/���.
    void StopMelody();
}
