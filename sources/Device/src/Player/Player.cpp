// 2024/03/18 15:45:12 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Player/Player.h"
#include "Player/Beeper.h"
#include "Hardware/Timer.h"
#include <cmath>


namespace Player
{
    static uint8 NextSample(float frequency);
}


void Player::Init()
{
    Beeper::Init();
}


void Player::CallbackOnTimer()
{
    Beeper::CallbackOnOutputSample(NextSample(1e3f));
}


uint8 Player::NextSample(float frequency)
{
    return (uint8)(125.0f + 125.0f * std::sinf(2.0f * 3.1415926f * frequency * (float)TIME_MS / 1000.f));
}
