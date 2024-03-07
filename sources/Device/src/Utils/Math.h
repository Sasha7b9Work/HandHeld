// 2024/03/07 20:23:55 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace Math
{
    template<class T>
    void CircleIncrease(T *value, T min, T max)
    {
        *value++;

        if (*value < min)
        {
            *value = max;
        }
        else if (*value > max)
        {
            *value = min;
        }
    }

    template<class T>
    void CircleDecrease(T *value, T min, T max)
    {
        *value--;

        if (*value < min)
        {
            *value = max;
        }
        else if (*value > max)
        {
            *value = min;
        }
    }

    template<class T>
    void CircleChange(T *value, T min, T max, T delta)
    {
        *value = *value + delta;

        if (*value < min)
        {
            *value = max;
        }
        else if (*value > max)
        {
            *value = min;
        }
    }
}
