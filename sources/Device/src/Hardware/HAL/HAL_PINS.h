// 2024/03/01 22:10:27 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


struct ModePin
{
    enum E
    {
        Output,
        Input,
        Count
    };
};


struct Pin
{
    Pin(uint _port, uint _pin, ModePin::E _mode) : port(_port), pin(_pin), mode(_mode) { }
    void Init();
protected:
    uint       port;
    uint       pin;
    ModePin::E mode;
};


struct PinIn : public Pin
{
    PinIn(uint _port, uint _pin) : Pin(_port, _pin, ModePin::Input) {}
    void Init();
};


struct PinOut : public Pin
{
    PinOut(uint _port, uint _pin) : Pin(_port, _pin, ModePin::Output) { }
    void Init();
    void ToLow() const;
    void ToHi() const;
};


extern PinIn pinSW_LEFT;
extern PinIn pinSW_DOWN;
extern PinIn pinSW_RIGHT;
extern PinIn pinSW_UP;

extern PinOut pinDOUT;
extern PinOut pinSCK;

extern PinIn  pinPWR_CTRL;
extern PinOut pinADC;

extern PinOut pinLEDPWR;
extern PinOut pinSOUND;
extern PinOut pinVIBRO;

extern PinIn pinPWR;
