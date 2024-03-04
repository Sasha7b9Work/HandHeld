/*
 * PCF8563.c
 *
 *	The MIT License.
 *  Created on: 5.09.2019
 *      Author: Mateusz Salamon
 *		Contact: mateusz@msalamon.pl
 *
 *      Website: https://msalamon.pl/dalsze-zmagania-z-rtc-ds1307-i-pcf8563-na-stm32/
 *      GitHub: https://github.com/lamik/PCF8563::RTC_STM32_HAL
 */
#include "defines.h"
#include "Modules/PCF8563/PCF8563.h"
#include "Hardware/HAL/HAL.h"


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

static uint8 Pcf8563Buffer[7];


namespace PCF8563
{
	static void CalculateDateTime(RTCDateTime *DateTime);
}

static void WriteBitToControlRegister(uint8 ControlRegister, uint8 BitNumber, bool bit)
{
    uint8 value = 0;

    // HAL_I2C_Mem_Read(hi2c_pcf8563, PCF8563::ADDRESS, ControlRegister ? PCF8563_REG_CONTROL_STATUS1 : PCF8563_REG_CONTROL_STATUS2, 1, &tmp, 1, PCF8563::I2C_TIMEOUT);
    HAL_I2C::Read(ControlRegister ? PCF8563_REG_CONTROL_STATUS1 : PCF8563_REG_CONTROL_STATUS2, &value, 1);

    if (bit)
    {
        value |= (1 << BitNumber);
    }
    else
    {
        value |= (1 << BitNumber);
    }

	if (ControlRegister == PCF8563_REG_CONTROL_STATUS1)				// Put zeros where zero is needed
	{
		value &= BINARY_U8(00011111);
	}
	else if (ControlRegister == PCF8563_REG_CONTROL_STATUS2)
	{
		value &= BINARY_U8(10101000);
	}

//    HAL_I2C_Mem_Write(hi2c_pcf8563, PCF8563::ADDRESS, ControlRegister ? PCF8563_REG_CONTROL_STATUS1 : PCF8563_REG_CONTROL_STATUS2, 1, &Value, 1, PCF8563::I2C_TIMEOUT);
	HAL_I2C::Write(ControlRegister ? PCF8563_REG_CONTROL_STATUS1 : PCF8563_REG_CONTROL_STATUS2, &value, 1);
}

void PCF8563::TEST1Enable(bool en)
{
	WriteBitToControlRegister(PCF8563_REG_CONTROL_STATUS1, PCF8563_CONTROL1_TEST1, en);
}

void PCF8563::STOPEnable(bool en)
{
	WriteBitToControlRegister(PCF8563_REG_CONTROL_STATUS1, PCF8563_CONTROL1_STOP, en);
}

void PCF8563::TESTCEnable(bool en)
{
	WriteBitToControlRegister(PCF8563_REG_CONTROL_STATUS1, PCF8563_CONTROL1_TESTC, en);
}

void PCF8563::InterruptEnable(bool en)
{
	WriteBitToControlRegister(PCF8563_REG_CONTROL_STATUS1, PCF8563_CONTROL2_TI_TP, en);
}

void PCF8563::AlarmFlagEnable(bool en)
{
    WriteBitToControlRegister(PCF8563_REG_CONTROL_STATUS1, PCF8563_CONTROL2_AF, en);
}

void PCF8563::TimerFlagEnable(bool en)
{
    WriteBitToControlRegister(PCF8563_REG_CONTROL_STATUS1, PCF8563_CONTROL2_TF, en);
}

void PCF8563::AlarmInterruptEnable(bool en)
{
    WriteBitToControlRegister(PCF8563_REG_CONTROL_STATUS1, PCF8563_CONTROL2_AIE, en);
}

void PCF8563::TimerInterruptEnable(bool en)
{
    WriteBitToControlRegister(PCF8563_REG_CONTROL_STATUS1, PCF8563_CONTROL2_TIE, en);
}

void PCF8563::ClkoutFrequency(CLKOUT_Freq Frequency)
{
    uint8 value = 0;

//    HAL_I2C_Mem_Read(hi2c_pcf8563, PCF8563::ADDRESS, PCF8563_REG_CLKOUT, 1, &tmp, 1, PCF8563::I2C_TIMEOUT);
	HAL_I2C::Read(PCF8563_REG_CLKOUT, &value, 1);
    value &= ~(3 << PCF8563_CLKOUT_CONTROL_FD0);
    value |= (Frequency << PCF8563_CLKOUT_CONTROL_FD0);

	//    HAL_I2C_Mem_Write(hi2c_pcf8563, PCF8563::ADDRESS, PCF8563_REG_CLKOUT, 1, &tmp, 1, PCF8563::I2C_TIMEOUT);
	HAL_I2C::Write(PCF8563_REG_CLKOUT, &value, 1);

	uint8 value2 = 0;

	HAL_I2C::Read(PCF8563_REG_CLKOUT, &value2, 1);

	if (value == value2)
	{
		value = value;
	}
	else
	{
		value = value;
	}
}

static uint8 bcd2dec(uint8 BCD)
{
    return (uint8)((((BCD & 0xF0) >> 4) * 10) + (BCD & 0xF));
}

static uint8 dec2bcd(uint8 DEC)
{
	return (uint8)(((DEC / 10) << 4) + (DEC % 10));
}

static int dayofweek(int Day, int Month, int Year)
{
	int Y, C, M, N, D;
	M = 1 + (9 + Month) % 12;
	Y = Year - (M > 10);
	C = Y / 100;
	D = Y % 100;
	N = ((13 * M - 1) / 5 + D + D / 4 + 6 * C + Day + 5) % 7;
	return (7 + N) % 7;
}

void PCF8563::SetDateTime(RTCDateTime *DateTime)
{
	uint8 tmp[7];

	if (DateTime->Second > 59) DateTime->Second = 59;
	if (DateTime->Minute > 59) DateTime->Minute = 59;
	if (DateTime->Hour > 23) DateTime->Hour = 23;
	if (DateTime->Day > 31) DateTime->Day = 31;
	if (DateTime->Month > 12) DateTime->Month = 12;
	if (DateTime->Year > 2099) DateTime->Year = 2099;

	tmp[0] = dec2bcd((uint8)((DateTime->Second) & 0x7F));
	tmp[1] = dec2bcd(DateTime->Minute);
	tmp[2] = dec2bcd(DateTime->Hour);
	tmp[3] = dec2bcd(DateTime->Day);
	tmp[4] = (uint8)dayofweek(DateTime->Day, DateTime->Month, DateTime->Year);
	tmp[5] = dec2bcd(DateTime->Month);
	tmp[6] = dec2bcd((uint8)(DateTime->Year - 2000));

	// HAL_I2C_Mem_Write(hi2c_pcf8563, PCF8563::ADDRESS, PCF8563_REG_TIME, 1, tmp, 7, PCF8563::I2C_TIMEOUT);
	HAL_I2C::Write(PCF8563_REG_TIME, tmp, 7);
}

void PCF8563::CalculateDateTime(RTCDateTime *DateTime)
{
	DateTime->Second = bcd2dec((uint8)((Pcf8563Buffer[0]) & 0x7F));
	DateTime->Minute = bcd2dec(Pcf8563Buffer[1]);
	DateTime->Hour = bcd2dec(Pcf8563Buffer[2]);
	DateTime->Day = Pcf8563Buffer[3];
	DateTime->DayOfWeek = bcd2dec((uint8)(Pcf8563Buffer[4] + 1)); // too keep weekdays in 1-7 format
	DateTime->Month = bcd2dec((uint8)(Pcf8563Buffer[5] & 0x1F));
	DateTime->Year = (uint16)(2000 + bcd2dec(Pcf8563Buffer[6]));
}

void PCF8563::GetDateTime(RTCDateTime *DateTime)
{
//	HAL_I2C_Mem_Read(hi2c_pcf8563, PCF8563::ADDRESS, PCF8563_REG_TIME, 1, Pcf8563Buffer, 7, PCF8563::I2C_TIMEOUT);
	HAL_I2C::Read(PCF8563_REG_TIME, Pcf8563Buffer, 7);

	PCF8563::CalculateDateTime(DateTime);
}

void PCF8563::Init()
{
	PCF8563::ClkoutFrequency(CLKOUT_FREQ_1HZ);
	PCF8563::STOPEnable(0);
}
