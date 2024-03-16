// 2024/03/03 17:06:14 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace Beeper
{
    void Init();

    void Beep();

    // Вызывается плеером, когда игрок мелодия стартует (из StartMelody()). Может использоваться для настройки таймера/ШИМ.
    void StartMelody();

    // Вывод отсчёта
    void OutputSample(uint8);

    // Вызывается проигрывателем после завершения мелодии (из TimerFunc(), прерывания отключены).
    // Может использоваться для настройки таймера/ШИМ.
    void StopMelody();
}
