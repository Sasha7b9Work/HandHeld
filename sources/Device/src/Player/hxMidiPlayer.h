#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "hxMidiPlayer_Config.h"


#ifdef HXMIDIPLAYER_USE_COMPRESSION

struct TMelody
{
    const uint8 *m_pStream1;
    const uint8 *m_pStream2;
};

#else

struct TPlayerStateChange
{
    //highest bit is highest for channel index        
    uint8     m_noteNumber;

    ///15-3 bits - Delta value, 2,1,0 bits - channel index  
    uint16    m_delta;
};

struct TMelody
{
    const TPlayerStateChange *m_pEvents;
};

#endif


namespace Player
{
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
