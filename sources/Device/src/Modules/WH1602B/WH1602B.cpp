// 2024/04/29 21:49:15 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Modules/WH1602B/WH1602B.h"
#include "Hardware/HAL/HAL_PINS.h"
#include <gd32e23x.h>


namespace WH1602B
{
#define BUSY_CYCLE_TIME				(5u)	/* x 10us. See datasheet for minimal value. */
#define CLRSCR_CYCLE_TIME			(200u)	/* x 10us. See datasheet for minimal value. */
#define RETHOME_CYCLE_TIME			(200u)	/* x 10us. See datasheet for minimal value. */
#define INIT_CYCLE_TIME				(400u)

#define DISPLAY_CONFIG_4bit_2L_5x8		(0x28u) /* Use 4-bit interface, 2 or 4 Lines, 5x8 pixel resolution */
#define DISPLAY_CONFIG_4bit_1L_5x8		(0x20u) /* Use 4-bit interface, 1 Line, 5x8 pixel resolution */

#define VIEW_MODE_DispOn_BlkOn_CrsOn	(0x0Fu) /* Display On, Blink On, Cursor On */
#define VIEW_MODE_DispOn_BlkOff_CrsOn	(0x0Eu) /* Display On, Blink Off, Cursor On */
#define VIEW_MODE_DispOn_BlkOn_CrsOff	(0x0Du) /* Display On, Blink On, Cursor Off */
#define VIEW_MODE_DispOn_BlkOff_CrsOff	(0x0Cu) /* Display On, Blink Off, Cursor Off */
#define VIEW_MODE_DispOff_BlkOff_CrsOff	(0x08u) /* Display Off, Blink Off, Cursor Off */

#define ENTRY_MODE_DEC_NO_SHIFT			(0x04u)
#define ENTRY_MODE_DEC_WITH_SHIFT     	(0x05u)
#define ENTRY_MODE_INC_NO_SHIFT	      	(0x06u)
#define ENTRY_MODE_INC_WITH_SHIFT     	(0x07u)

#define DEFAULT_DISPLAY_CONFIG		DISPLAY_CONFIG_4bit_2L_5x8
#define DEFAULT_VIEW_MODE			VIEW_MODE_DispOn_BlkOff_CrsOff
#define DEFAULT_ENTRY_MODE			ENTRY_MODE_INC_NO_SHIFT


// PB1
#define SET_EN()    pinEN.ToHi()
#define CLR_EN()    pinEN.ToLow()
// PB0
#define SET_RS()    pinRS.ToHi()
#define CLR_RS()    pinRS.ToLow()
// PA4
#define SET_D7()    pinD7.ToHi()
#define CLR_D7()    pinD7.ToLow()
// PA5
#define SET_D6()    pinD6.ToHi()
#define CLR_D6()    pinD6.ToLow()
// PA6
#define SET_D5()    pinD5.ToHi()
#define CLR_D5()    pinD5.ToLow()
// PA7
#define SET_D4()    pinD4.ToHi()
#define CLR_D4()    pinD4.ToLow()
// PB2
#define SET_PWR()   pinPWR.ToHi()
#define CLR_PWR()   pinPWR.ToLow()

#define DATA_7_MASK     0x80u
#define DATA_6_MASK     0x40u
#define DATA_5_MASK     0x20u
#define DATA_4_MASK     0x10u
#define DATA_3_MASK     0x08u
#define DATA_2_MASK     0x04u
#define DATA_1_MASK     0x02u
#define DATA_0_MASK     0x01u

#define MCU_FREQ_VALUE (78000000 / 1000000U) //MCU clock frequency in MHz

#define ENABLE_CYCLE_TIME	1u	/* Minimal value ~ 1us */
#define AC_UPDATE_TIME		4u	/* Minimal value ~ 4us */

    static void lcdWrite(uint8 data);
    static void lcd10usDelay(volatile uint us);
    static void lcdConfig(uint8 param);
    static void lcdSetMode(uint8 param);
    static void lcdClrScr();
    static void lcdReturn();
    static void lcdHigh(uint8 data);
    static void lcdStrobe();
    static void lcdLow(uint8 data);

    static PinOut pinEN(GPIOB, GPIO_PIN_1);
    static PinOut pinRS(GPIOB, GPIO_PIN_0);
    static PinOut pinD7(GPIOA, GPIO_PIN_4);
    static PinOut pinD6(GPIOA, GPIO_PIN_5);
    static PinOut pinD5(GPIOA, GPIO_PIN_6);
    static PinOut pinD4(GPIOA, GPIO_PIN_7);
    static PinOut pinPWR(GPIOB, GPIO_PIN_2);
}


void WH1602B::Init()
{
    pinPWR.Init();
    pinPWR.ToHi();

    pinEN.Init();
    pinRS.Init();
    pinD4.Init();
    pinD5.Init();
    pinD6.Init();
    pinD7.Init();

    lcdWrite(0x30);
    lcd10usDelay(INIT_CYCLE_TIME);
    lcdWrite(0x30);
    lcd10usDelay(INIT_CYCLE_TIME);

    lcdConfig(DEFAULT_DISPLAY_CONFIG);
    lcdSetMode(DEFAULT_VIEW_MODE);
    lcdSetMode(DEFAULT_ENTRY_MODE);
    lcdClrScr();
    lcdReturn();
}


void WH1602B::Write(int num_row, uint8 buffer[8])
{
    CLR_RS();                   // Посылаем команду
    uint8 command = 0x80;       // Set DDRAM address
    command |= num_row * 2;

    lcdWrite(command);

    SET_RS();                   // Посылаем данные

    for (int i = 0; i < 8; i++)
    {
        lcdWrite(buffer[i]);
    }
}


void WH1602B::lcdWrite(uint8 data)
{
    lcdHigh(data);
    lcdStrobe();
    lcdLow(data);
    lcdStrobe();
    /* The busy flag must be checked after the 4-bit data has been transferred twice. */
    lcd10usDelay(BUSY_CYCLE_TIME);
}


void WH1602B::lcdConfig(uint8 param)
{
    /* Send commands to LCD. */
    CLR_RS();

    lcdHigh(param);
    lcdStrobe();		// Change 8-bit interface to 4-bit interface
    lcd10usDelay(BUSY_CYCLE_TIME);
    lcdStrobe();		/* DB7 to DB4 of the "Function set" instruction is written twice. */
    lcd10usDelay(BUSY_CYCLE_TIME);
    lcdLow(param);
    lcdStrobe();		// 4-bit, two lines, 5x8 pixel
    lcd10usDelay(BUSY_CYCLE_TIME);
    /* Note: The number of display lines and character font cannot be changed after this point. */
}


void WH1602B::lcd10usDelay(volatile uint us)
{
    /* Conversion to us */
    us *= MCU_FREQ_VALUE;
    /* Wait */
    while (us > 0u)
    {
        us--;
    }
}


void WH1602B::lcdSetMode(uint8 param)
{
    CLR_RS();
    lcdWrite(param);
}


void WH1602B::lcdStrobe(void)
{/* Low level function. */
    SET_EN();
    lcd10usDelay(ENABLE_CYCLE_TIME);
    CLR_EN();
}


void WH1602B::lcdClrScr(void)
{
    CLR_RS();
    /* Clear screen */
    lcdWrite(0x01u);
    /* Busy delay */
    lcd10usDelay(CLRSCR_CYCLE_TIME);
}


void WH1602B::lcdLow(uint8 data)
{/* Low level function. */
    if (data & DATA_3_MASK) SET_D7(); else CLR_D7();
    if (data & DATA_2_MASK) SET_D6(); else CLR_D6();
    if (data & DATA_1_MASK) SET_D5(); else CLR_D5();
    if (data & DATA_0_MASK) SET_D4(); else CLR_D4();
}


void WH1602B::lcdHigh(uint8 data)
{/* Low level function. */
    if (data & DATA_7_MASK) SET_D7(); else CLR_D7();
    if (data & DATA_6_MASK) SET_D6(); else CLR_D6();
    if (data & DATA_5_MASK) SET_D5(); else CLR_D5();
    if (data & DATA_4_MASK) SET_D4(); else CLR_D4();
}


void WH1602B::lcdReturn(void)
{
    CLR_RS();
    /* Return home */
    lcdWrite(0x02u);
    /* Busy delay */
    lcd10usDelay(RETHOME_CYCLE_TIME);
}
