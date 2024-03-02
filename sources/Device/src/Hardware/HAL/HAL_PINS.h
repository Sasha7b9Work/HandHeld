// 2024/03/01 22:10:27 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


struct Pin
{
    void Init();
};


struct PinIn : public Pin
{

};


struct PinOut : public Pin
{
    void ToLow() const;
    void ToHi() const;
};


extern PinIn pinSW_LEFT;
extern PinIn pinSW_DOWN;
extern PinIn pinSW_RIGHT;
extern PinIn pinSW_UP;

extern Pin pinDOUT;
extern Pin pinSCK;

extern PinIn  pinPWR_CTRL;
extern PinOut pinADC;

extern PinOut pinLEDPWR;
extern PinOut pinSOUND;
extern PinOut pinVIBRO;

extern PinOut pinTFT_DC;
extern PinOut pinTFT_RES;
extern PinOut pinTFT_BKG;
extern PinOut pinTFT_SCL;
extern PinOut pinTFT_SDA;

extern PinIn pinPWR;
