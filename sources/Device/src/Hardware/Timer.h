// 2024/03/02 09:30:18 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace Timer
{
    void Delay(uint timeMS);
}


struct TimeMeterMS
{
    void Reset();

    uint ElapsedTime() const;
};
