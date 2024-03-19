// 2024/03/18 15:45:12 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Player/Player.h"
#include "Player/Beeper.h"
#include "Hardware/Timer.h"
#include <cmath>


struct Note
{
    uint16 frequency;       // В герцах
    uint8  duration;        // В 100 мс
    uint8  velocity;        // 10 градаций - от 0 до 9
};


struct Sound
{
    const Note *const notes;        // В конце мелодии нулевые значения
};


#include "Player/Sounds/sound1.h"


namespace Player
{

}


void Player::Init()
{
    Beeper::Init();
}


void Player::Play(TypeSound::E)
{

}


void Player::CallbackOnTimer()
{
}
