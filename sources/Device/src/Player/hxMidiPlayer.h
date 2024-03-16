#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "hxMidiPlayer_Config.h"


#ifdef HXMIDIPLAYER_USE_COMPRESSION
    
///=====================================================
///=====================================================
typedef struct 
{
    const uint8_t* m_pStream1;          
    const uint8_t* m_pStream2;              
} TMelody;
    
#else

///=====================================================
///=====================================================
typedef struct 
{
    //highest bit is highest for channel index        
    uint8_t     m_noteNumber;
    
    ///15-3 bits - Delta value, 2,1,0 bits - channel index  
    uint16_t    m_delta;          
} TPlayerStateChange;

///=====================================================
///=====================================================
typedef struct 
{
    const flash TPlayerStateChange*  m_pEvents;              
} TMelody;
    
#endif

//======== Timer function ===========

///Timer event function, should be called by user with fixed frequency HXMIDIPLAYER_SAMPLING_RATE
extern void Player_TimerFunc();

// ======== Control functions ===========

///Start playing melody
//Previously played melody is stoped, Player_Finished callback is called.
//Player_Started() callback is called on start.
//_delay - start delay in 255Hz ticks, max is 65534
extern void Player_StartMelody( const TMelody* _pMelody, uint16_t _delay );

/// ======== Misc functions ===========

///Is player currently playing ?
extern bool Player_IsPlaying();  

///Wait untill player finish playing
//If not playing currently, returns immediatelly.
extern void Player_WaitFinish();  

//Stop currently played melody.
//Player_Finished() callback is called if was playing.
//If melody is not playing - call is ignored completely.
void Player_Stop();
