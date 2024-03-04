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

#define PCF8563_ADDRESS                 (0x51<<1)
#define PCF8563_I2C_TIMEOUT             100

#define PCF8563_REG_CONTROL_STATUS1     ((uint8)0x00)
#define PCF8563_REG_CONTROL_STATUS2     ((uint8)0x01)
#define PCF8563_REG_TIME                ((uint8)0x02)
#define PCF8563_REG_SECONDS             ((uint8)0x02)
#define PCF8563_REG_MINUTES             ((uint8)0x03)
#define PCF8563_REG_HOURS               ((uint8)0x04)
#define PCF8563_REG_DATE                ((uint8)0x05)
#define PCF8563_REG_WEEKDAY             ((uint8)0x06)
#define PCF8563_REG_MONTH               ((uint8)0x07)
#define PCF8563_REG_YEAR                ((uint8)0x08)
#define PCF8563_REG_ALARM_MINUTE        ((uint8)0x09)
#define PCF8563_REG_ALARM_HOUR          ((uint8)0x0A)
#define PCF8563_REG_ALARM_DAY           ((uint8)0x0B)
#define PCF8563_REG_ALARM_WEEKDAY       ((uint8)0x0C)
#define PCF8563_REG_CLKOUT              ((uint8)0x0D)
#define PCF8563_REG_TIMER_CONTROL       ((uint8)0x0E)
#define PCF8563_REG_TIMER               ((uint8)0x0F)

//
//	Controll register 1 0x00
//
#define PCF8563_CONTROL1_TEST1		7
#define PCF8563_CONTROL1_STOP		5
#define PCF8563_CONTROL1_TESTC		3

//
//	Controll register 2 0x01
//
#define PCF8563_CONTROL2_TI_TP		4
#define PCF8563_CONTROL2_AF			3
#define PCF8563_CONTROL2_TF			2
#define PCF8563_CONTROL2_AIE		1
#define PCF8563_CONTROL2_TIE		0

//
//	CLKOUT control register 0x0D
//
#define PCF8563_CLKOUT_CONTROL_FE				7
#define PCF8563_CLKOUT_CONTROL_FD1				1
#define PCF8563_CLKOUT_CONTROL_FD0				0

typedef enum
{
    CLKOUT_FREQ_32768HZ = 0,
    CLKOUT_FREQ_1024HZ  = 1,
    CLKOUT_FREQ_32HZ    = 2,
    CLKOUT_FREQ_1HZ     = 3,
	Count
} CLKOUT_Freq;


typedef struct
{
	uint16 	Year;
	uint8  	Month;
	uint8		Day;
	uint8		Hour;
	uint8		Minute;
	uint8		Second;
	uint8		DayOfWeek;
}RTCDateTime;


namespace PCF8563
{
    void TEST1Enable(uint8 Enable);
    void STOPEnable(uint8 Enable);
    void TESTCEnable(uint8 Enable);
    void InterruptEnable(uint8 Enable);
    void AlarmFlagEnable(uint8 Enable);
    void TimerFlagEnable(uint8 Enable);
    void AlarmInterruptEnable(uint8 Enable);
    void TimerInterruptEnable(uint8 Enable);
    void ClkoutFrequency(CLKOUT_Freq Frequency);
    void GetDateTime(RTCDateTime *DateTime);        // Use in blocking/interrupt mode in PCF8563_INT EXTI handler
    void SetDateTime(RTCDateTime *DateTime);
    void Init();
}
