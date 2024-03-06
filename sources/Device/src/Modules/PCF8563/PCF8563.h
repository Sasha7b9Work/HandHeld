/*
 * PCF8563.h
 *
 *  The MIT License.
 *  Created on: 5.09.2019
 *      Author: Mateusz Salamon
 *      Contact: mateusz@msalamon.pl
 *
 *      Website: https://msalamon.pl/dalsze-zmagania-z-rtc-ds1307-i-pcf8563-na-stm32/
 *      GitHub: https://github.com/lamik/PCF8563_RTC_STM32_HAL
 */

 //
 // Uncomment when you are using DMA reading
 //


typedef enum
{
    CLKOUT_FREQ_32768HZ = 0,
    CLKOUT_FREQ_1024HZ  = 1,
    CLKOUT_FREQ_32HZ    = 2,
    CLKOUT_FREQ_1HZ     = 3,
    Count
} CLKOUT_Freq;


struct RTCDateTime
{
    uint16  Year;
    uint8   Month;
    uint8   Day;
    uint8   Hour;
    uint8   Minute;
    uint8   Second;
    uint8   DayOfWeek;
};


namespace PCF8563
{
    void Init();

    void Update();

    void TEST1Enable(bool);

    void STOPEnable(bool);

    void TESTCEnable(bool);

    void InterruptEnable(bool);

    void AlarmFlagEnable(bool);

    void TimerFlagEnable(bool);

    void AlarmInterruptEnable(bool);

    void TimerInterruptEnable(bool);

    void SetTimer(uint time_sec);

    void ClkoutFrequency(CLKOUT_Freq);

    void GetDateTime(RTCDateTime *);        // Use in blocking/interrupt mode in PCF8563_INT EXTI handler

    void SetDateTime(RTCDateTime *);
}
