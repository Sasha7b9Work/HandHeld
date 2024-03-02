// 2024/03/01 22:10:32 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/HAL/HAL_PINS.h"


PinIn pinSW_LEFT;       // PB0  18 
PinIn pinSW_DOWN;       // PB1  19
PinIn pinSW_RIGHT;      // PB2  20
PinIn pinSW_UP;         // PA7  17

Pin pinDOUT;            // PB12 25
Pin pinSCK;             // PB13 26

PinIn  pinPWR_CTRL;     // PA0  10
PinOut pinADC;          // PA1  11

PinOut pinLEDPWR;       // PA2  12
PinOut pinSOUND;        // PA3  13
PinOut pinVIBRO;        // PA10 31

PinOut pinTFT_DC;       // PA5  15
PinOut pinTFT_RES;      // PA8  29
PinOut pinTFT_BKG;      // PA9  30
PinOut pinTFT_SCL;      // PA4  14
PinOut pinTFT_SDA;      // PA6  16

PinIn pinPWR;           // PA12 33


void Pin::Init()
{

}


void PinOut::ToLow() const
{

}


void PinOut::ToHi() const
{

}
