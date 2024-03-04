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

static uint8 Pcf8563Buffer[7];


namespace PCF8563
{
	static void CalculateDateTime(RTCDateTime *DateTime);
}

static void WriteBitToControlRegister(uint8 ControlRegister, uint8 BitNumber, uint8 Value)
{
    uint8 tmp;

    if (Value > 1) Value = 1;
    if (ControlRegister > 1) Value = 1;
    if (BitNumber > 7) Value = 7;

    // HAL_I2C_Mem_Read(hi2c_pcf8563, PCF8563::ADDRESS, ControlRegister ? PCF8563_REG_CONTROL_STATUS1 : PCF8563_REG_CONTROL_STATUS2, 1, &tmp, 1, PCF8563::I2C_TIMEOUT);
    HAL_I2C::Read(ControlRegister ? PCF8563_REG_CONTROL_STATUS1 : PCF8563_REG_CONTROL_STATUS2, &tmp, 1);

    tmp &= ~(1 << BitNumber);
    tmp |= (Value << BitNumber);

    ControlRegister ? (Value &= BINARY_U8(10101000)) : (Value &= BINARY_U8(00011111)); // Put zeros where zero is needed

//    HAL_I2C_Mem_Write(hi2c_pcf8563, PCF8563::ADDRESS, ControlRegister ? PCF8563_REG_CONTROL_STATUS1 : PCF8563_REG_CONTROL_STATUS2, 1, &Value, 1, PCF8563::I2C_TIMEOUT);
	HAL_I2C::Write(ControlRegister ? PCF8563_REG_CONTROL_STATUS1 : PCF8563_REG_CONTROL_STATUS2, &Value, 1);
}

void PCF8563::TEST1Enable(uint8 Enable)
{
	WriteBitToControlRegister(PCF8563_REG_CONTROL_STATUS1, PCF8563_CONTROL1_TEST1, Enable);
}

void PCF8563::STOPEnable(uint8 Enable)
{
	WriteBitToControlRegister(PCF8563_REG_CONTROL_STATUS1, PCF8563_CONTROL1_STOP, Enable);
}

void PCF8563::TESTCEnable(uint8 Enable)
{
	WriteBitToControlRegister(PCF8563_REG_CONTROL_STATUS1, PCF8563_CONTROL1_TESTC, Enable);
}

void PCF8563::InterruptEnable(uint8 Enable)
{
	WriteBitToControlRegister(PCF8563_REG_CONTROL_STATUS1, PCF8563_CONTROL2_TI_TP, Enable);
}

void PCF8563::AlarmFlagEnable(uint8 Enable)
{
    WriteBitToControlRegister(PCF8563_REG_CONTROL_STATUS1, PCF8563_CONTROL2_AF, Enable);
}

void PCF8563::TimerFlagEnable(uint8 Enable)
{
    WriteBitToControlRegister(PCF8563_REG_CONTROL_STATUS1, PCF8563_CONTROL2_TF, Enable);
}

void PCF8563::AlarmInterruptEnable(uint8 Enable)
{
    WriteBitToControlRegister(PCF8563_REG_CONTROL_STATUS1, PCF8563_CONTROL2_AIE, Enable);
}

void PCF8563::TimerInterruptEnable(uint8 Enable)
{
    WriteBitToControlRegister(PCF8563_REG_CONTROL_STATUS1, PCF8563_CONTROL2_TIE, Enable);
}

void PCF8563::ClkoutFrequency(CLKOUT_Freq Frequency)
{
    uint8 tmp;

    if (Frequency > 3)
    {
        Frequency = CLKOUT_FREQ_1HZ;
    }

//    HAL_I2C_Mem_Read(hi2c_pcf8563, PCF8563::ADDRESS, PCF8563_REG_CLKOUT, 1, &tmp, 1, PCF8563::I2C_TIMEOUT);
	HAL_I2C::Read(PCF8563_REG_CLKOUT, &tmp, 1);

    tmp &= ~(3 << PCF8563_CLKOUT_CONTROL_FD0);
    tmp |= (Frequency << PCF8563_CLKOUT_CONTROL_FD0);

//    HAL_I2C_Mem_Write(hi2c_pcf8563, PCF8563::ADDRESS, PCF8563_REG_CLKOUT, 1, &tmp, 1, PCF8563::I2C_TIMEOUT);
	HAL_I2C::Write(PCF8563_REG_CLKOUT, &tmp, 1);
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
