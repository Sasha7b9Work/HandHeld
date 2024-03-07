// 2024/03/02 09:30:18 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


#define TIME_MS timer_counter


namespace Timer
{
    void Delay(uint timeMS);
}


struct TimeMeterMS
{
    TimeMeterMS()
    {
        Reset();
    }

    void Reset();

    uint ElapsedTime() const;

private:

    uint time_reset;
};


extern uint timer_counter;
