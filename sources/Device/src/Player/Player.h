#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "Player/PlayerConfig.h"


struct TMelody
{
    const uint8 *m_pStream1;
    const uint8 *m_pStream2;
};


namespace Player
{
    void Init();

    // Is player currently playing ?
    bool IsPlaying();

    // Wait untill player finish playing
    // If not playing currently, returns immediatelly.
    void WaitFinish();

    // Stop currently played melody.
    // Player_Finished() callback is called if was playing.
    // If melody is not playing - call is ignored completely.
    void Stop();
}
