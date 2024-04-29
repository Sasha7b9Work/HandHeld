/*
 * HD44780 symbol display driver.
 *
 * Copyright 2023 Mikhail Belkin <dltech174@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include <stdarg.h>
#include "ru_font.h"
#include "hd44780.h"
#include "hd44780_stuff.h"
#include "../stm32/gpio.h"
#include "../stm32/delay.h"

volatile uint8_t pos=0;
volatile uint8_t posy=0;
const uint32_t portBus[8] = { D0_PORT, D1_PORT, D2_PORT, D3_PORT,\
                              D4_PORT, D5_PORT, D6_PORT, D7_PORT };
const uint32_t pinBus[8]  = { D0_PIN, D1_PIN, D2_PIN, D3_PIN,\
                              D4_PIN, D5_PIN, D6_PIN, D7_PIN };

void setBus(uint8_t byte, uint8_t isHalf);
void lcdTrans(uint8_t byte);
uint8_t lcdRead(void);
void lcdWaitForBusy(uint8_t tOut);
void lcdCommand(uint8_t cmd);
void lcdWriteRamm(uint8_t data);

#ifdef PROGRAM_RU
uint8_t cyclicBuffer[8] = {0};
void cyrillicParser(uint8_t c);
uint8_t loadSymbol(uint8_t code, const uint8_t *symbol);
#endif

void setBus(uint8_t byte, uint8_t isHalf)
{
    uint8_t size, pinShift;
    if(isHalf > 0) {
        size = 4;
        pinShift = 4;
    } else {
        size = 8;
        pinShift = 0;
    }
    for(uint8_t i=0 ; i<size ; ++i) {
        if( ((byte>>i) & 0x01) > 0 ) {
            gpioSet(portBus[i+pinShift], pinBus[i+pinShift]);
        } else {
            gpioReset(portBus[i+pinShift], pinBus[i+pinShift]);
        }
    }
    gpioSet(E_PORT, E_PIN);
    rough_delay_us(BIT_DELAY_US);
    gpioReset(E_PORT, E_PIN);
    rough_delay_us(BIT_DELAY_US);
}

void lcdTrans(uint8_t byte)
{
#ifndef RW_DISABLE
    gpioReset(RW_PORT, RW_PIN);
#endif
#ifdef LCD_8BIT
    setBus(byte, 0);
#endif
#ifdef LCD_4BIT
    setBus(byte>>4, 1);
    setBus(byte, 1);
#endif
}

#ifndef RW_DISABLE
uint8_t lcdRead()
{
    uint8_t ret = 0;
    gpioSet(RW_PORT, RW_PIN);
#ifdef LCD_8BIT
    for(uint8_t i=0 ; i<8 ; ++i) {
        gpioSetInput(portBus[i], pinBus[i]);
    }
    gpioSet(E_PORT, E_PIN);
    rough_delay_us(BIT_DELAY_US);
    for(uint8_t i=0 ; i<8 ; ++i) {
        if( gpioIsActive(portBus[i], pinBus[i]) ) {
            ret |= 1<<i;
        }
    }
    gpioReset(E_PORT, E_PIN);
    for(uint8_t i=0 ; i<8 ; ++i) {
        gpioSetPushPull(portBus[i], pinBus[i]);
    }
#endif
#ifdef LCD_4BIT
    for(uint8_t i=4 ; i<8 ; ++i) {
        gpioSetInput(portBus[i], pinBus[i]);
    }
    gpioSet(E_PORT, E_PIN);
    rough_delay_us(BIT_DELAY_US);
    for(uint8_t i=4 ; i<8 ; ++i) {
        if( gpioIsActive(portBus[i], pinBus[i]) ) {
            ret |= 1<<i;
        }
    }
    gpioReset(E_PORT, E_PIN);
    rough_delay_us(BIT_DELAY_US);
    gpioSet(E_PORT, E_PIN);
    rough_delay_us(BIT_DELAY_US);
    for(uint8_t i=0 ; i<4 ; ++i) {
        if( gpioIsActive(portBus[i+4], pinBus[i+4]) ) {
            ret |= 1<<i;
        }
    }
    gpioReset(E_PORT, E_PIN);
    for(uint8_t i=4 ; i<8 ; ++i) {
        gpioSetPushPull(portBus[i], pinBus[i]);
    }
    rough_delay_us(BIT_DELAY_US);
#endif
    return ret;
}
#endif

void lcdWaitForBusy(uint8_t tOut)
{
#ifdef RW_DISABLE
    rough_delay_us(tOut);
#else
    gpioReset(RS_PORT, RS_PIN);
    uint8_t ret = BF;
//    tOut = 200;
    while( ((ret & BF) > 0) && (--tOut > 0) ) {
        ret = lcdRead();
    }
#endif
}

void lcdCommand(uint8_t cmd)
{
    gpioReset(RS_PORT, RS_PIN);
    lcdTrans(cmd);
    lcdWaitForBusy(COMMAND_DELAY_US);
}

void lcdWriteRamm(uint8_t data)
{
    gpioSet(RS_PORT, RS_PIN);
    lcdTrans(data);
    lcdWaitForBusy(COMMAND_DELAY_US);
//    gpioReset(RS_PORT, RS_PIN);
}

void lcdInit()
{
#ifndef RW_DISABLE
    gpioSetPushPull(RW_PORT, RW_PIN);
#endif
    gpioSetPushPull(RS_PORT, RS_PIN);
    gpioSetPushPull(E_PORT, E_PIN);
    // the display is turning on during 10 ms
    delay_ms(SWON_DELAY_MS);
#ifdef LCD_8BIT
    for(uint8_t i=0 ; i<8 ; ++i) {
        gpioSetPushPull(portBus[i], pinBus[i]);
    }
    lcdCommand(FUNCTION_SET | F_N | F_DL);
    delay_ms(CLRSCR_DELAY_MS);
    lcdCommand(FUNCTION_SET | F_N | F_DL);
    delay_ms(SETBUS_DELAY_MS);
#endif
#ifdef LCD_4BIT
    for(uint8_t i=4 ; i<8 ; ++i) {
        gpioSetPushPull(portBus[i], pinBus[i]);
    }
    gpioReset(RS_PORT, RS_PIN);
    setBus(0x03, 1);
    delay_ms(CLRSCR_DELAY_MS);
    setBus(0x03, 1);
    delay_ms(SETBUS_DELAY_MS);
    setBus(0x02, 1);
    delay_ms(SETBUS_DELAY_MS);
    lcdCommand(FUNCTION_SET | F_N);
    delay_ms(SETBUS_DELAY_MS);
#endif
    lcdCommand(DISPLAY_ON | F_D);
    delay_ms(SETBUS_DELAY_MS);
    lcdCommand(ENTRY_MODE_SET | F_ID);
    delay_ms(SETBUS_DELAY_MS);
    lcdClr();
}

void lcdClr()
{
    pos = 0;
    lcdCommand(CLEAR_DISPLAY);
    delay_ms(CLRSCR_DELAY_MS);
}

void lcdCursor(uint8_t state)
{
    uint8_t cmd;
    switch(state)
    {
        case CURSOR_OFF:
            cmd = DISPLAY_ON | F_D;
            break;
        case CURSOR_UNDERSCORE:
            cmd = DISPLAY_ON | F_D | F_C;
            break;
        case CURSOR_UNDERSCORE_BLINK:
            cmd = DISPLAY_ON | F_D | F_B | F_C;
            break;
        case CURSOR_BLINK:
            cmd = DISPLAY_ON | F_D | F_B;
            break;
        default:
            cmd = DISPLAY_ON | F_D;
    }
    lcdCommand(cmd);
}

void lcdPos(uint8_t x, uint8_t y)
{
    if(x > LCD_SIZE) x = LCD_SIZE;
    if(y > 1)  y = 1;
    pos = x;
//    lcdCommand(RETURN_HOME);
    if(y==1) {
        x += SECOND_STR_SFT;
        posy = 40;
    } else {
        posy = 0;
    }
    // for(uint8_t i=0 ; i<x ; ++i) {
    //     lcdCommand(CURSOR_SHIFT | RL);
    // }
    lcdCommand(SET_DDRAM_ADDR | x);
}

void lputc(char c)
{
    lcdWriteRamm(c);
    pos++;
    if(pos > LCD_SIZE) pos = LCD_SIZE;
}

void lputs(char *s)
{
    for(uint8_t i=0 ; i<LCD_SIZE ; ++i) {
        if(s[i] == 0) break;
        lcdWriteRamm(s[i]);
        pos++;
    }
}

void luputs(char *s)
{
    uint8_t i = 0;
    while((pos < LCD_SIZE) && (s[i] != 0)) {
        // ёмаё
        if( (s[i] == (uint8_t)(RU_UTF_E_UP>>8)) && (s[i+1] == (uint8_t)(RU_UTF_E_UP)) ) {
#ifdef PROGRAM_RU
            cyrillicParser(RU_U8_JO);
#else
            lputc(HD44780_E_UP);
#endif
            i++;
        } else if( (s[i] == (uint8_t)(RU_UTF_E_LOW>>8)) && (s[i+1] == (uint8_t)(RU_UTF_E_LOW)) ) {
#ifdef PROGRAM_RU
            cyrillicParser(RU_U8_jo);
#else
            lputc(HD44780_E_LOW);
#endif
            i++;
            // весь остальной русский юникодь
        } else if( (s[i] == RU_UTF_UPPER1) || (s[i] == RU_UTF_UPPER2) ) {
#ifdef PROGRAM_RU
            cyrillicParser(s[i+1]);
#else
            lputc(ru_utf8[s[i+1]-RU_UTF_SHIFT]);
#endif
            i++;
            // аски
        } else if( s[i] < ASCII_END ) {
            lputc(s[i]);
            // если не нашёль символь, то пробель
        } else {
            lputc(0x20);
        }
        i++;
    }
}

void lprintf(char *format, ... )
{
    char buffer[LCD_SIZE];
    va_list args;
    va_start (args, format);
    vsprintf (buffer, format, args);
    va_end (args);

    luputs(buffer);
}

void lcdCustomSymbol(uint8_t code, const uint8_t *symbol)
{
    if(code > 7) code = 7;
    lcdCommand(SET_CGRAM_ADDR | (code*8));
    for(uint8_t i=0 ; i<8 ; ++i) {
        lcdWriteRamm(symbol[i]&0x1f);
    }
    lcdCommand(SET_DDRAM_ADDR+pos+posy);
}

#ifdef PROGRAM_RU
uint8_t loadSymbol(uint8_t code, const uint8_t *symbol)
{
    uint8_t cyrillicCharacterAddr = 0x20;
    static uint8_t bufferPos = 0;
    // is the symbol already in codetable?
    for(uint8_t i=0 ; i<CUSTOM_SYMBOLS_NUMBER ; ++i)
    {
        if(cyclicBuffer[i] == code) {
            cyrillicCharacterAddr = i;
            break;
        }
        if(cyclicBuffer[i] == 0) break;
    }
    // if not, adding it
    if(cyrillicCharacterAddr == 0x20) {
        lcdCustomSymbol(bufferPos, (uint8_t*) symbol);
        cyclicBuffer[bufferPos] = code;
        cyrillicCharacterAddr = bufferPos;
        bufferPos++;
    }
    // loop the buffer
    if(bufferPos >= CUSTOM_SYMBOLS_NUMBER) bufferPos = 0;
    return cyrillicCharacterAddr;
}

void cyrillicParser(uint8_t c)
{
    switch(c)
    {
        case RU_U8_a:
            lputc('a');
            break;
        case RU_U8_b:
            lputc(loadSymbol(c, ru_b));
            break;
        case RU_U8_v:
            lputc(loadSymbol(c, ru_v));
            break;
        case RU_U8_g:
#ifdef ECONOMY_gr
            lputc('r');
#else
            lputc(loadSymbol(c, ru_g));
#endif
            break;
        case RU_U8_d:
#ifdef ECONOMY_dg
            lputc('g');
#else
            lputc(loadSymbol(c, ru_d));
#endif
            break;
        case RU_U8_e:
            lputc('e');
            break;
        case RU_U8_jo:
#ifdef ECONOMY_joe
            lputc('e');
#else
            lputc(loadSymbol(c, ru_jo));
#endif
            break;
        case RU_U8_zh:
            lputc(loadSymbol(c, ru_zh));
            break;
        case RU_U8_z:
            lputc(loadSymbol(c, ru_z));
            break;
        case RU_U8_i:
#ifdef ECONOMY_iu
            lputc('u');
#else
            lputc(loadSymbol(c, ru_i));
#endif
            break;
        case RU_U8_j:
#ifdef ECONOMY_ji
    #ifdef ECONOMY_iu
            lputc('u');
    #else
            lputc(loadSymbol(RU_U8_i, ru_i));
    #endif
#else
            lputc(loadSymbol(c, ru_j));
#endif
            break;
        case RU_U8_k:
#ifdef ECONOMY_kk
            lputc('k');
#else
            lputc(loadSymbol(c, ru_k));
#endif
            break;
        case RU_U8_l:
            lputc(loadSymbol(c, ru_l));
            break;
        case RU_U8_m:
#ifdef ECONOMY_mm
            lputc('m');
#else
            lputc(loadSymbol(c, ru_m));
#endif
            break;
        case RU_U8_n:
            lputc(loadSymbol(c, ru_n));
            break;
        case RU_U8_o:
            lputc('o');
            break;
        case RU_U8_p:
#ifdef ECONOMY_pn
            lputc('n');
#else
            lputc(loadSymbol(c, ru_p));
#endif
            break;
        case RU_U8_r:
            lputc('p');
            break;
        case RU_U8_s:
            lputc('c');
            break;
        case RU_U8_t:
            lputc(loadSymbol(c, ru_t));
            break;
        case RU_U8_u:
            lputc('y');
            break;
        case RU_U8_f:
            lputc(loadSymbol(c, ru_f));
            break;
        case RU_U8_h:
            lputc('x');
            break;
        case RU_U8_c:
            lputc(loadSymbol(c, ru_c));
            break;
        case RU_U8_ch:
#ifdef ECONOMY_ch4
            lputc('4');
#else
            lputc(loadSymbol(c, ru_ch));
#endif
            break;
        case RU_U8_sh:
            lputc(loadSymbol(c, ru_sh));
            break;
        case RU_U8_shh:
            lputc(loadSymbol(c, ru_shh));
            break;
        case RU_U8_tz:
#ifdef ECONOMY_tzmz
            lputc(loadSymbol(RU_U8_mz, ru_mz));
#else
            lputc(loadSymbol(c, ru_tz));
#endif
            break;
        case RU_U8_y:
            lputc(loadSymbol(c, ru_y));
            break;
        case RU_U8_mz:
            lputc(loadSymbol(c, ru_mz));
            break;
        case RU_U8_ee:
            lputc(loadSymbol(c, ru_e));
            break;
        case RU_U8_ju:
            lputc(loadSymbol(c, ru_ju));
            break;
        case RU_U8_ja:
            lputc(loadSymbol(c, ru_ja));
            break;
        case RU_U8_A:
            lputc('A');
            break;
        case RU_U8_B:
            lputc(loadSymbol(c, ru_B));
            break;
        case RU_U8_V:
            lputc('B');
            break;
        case RU_U8_G:
            lputc(loadSymbol(c, ru_G));
            break;
        case RU_U8_D:
            lputc(loadSymbol(c, ru_D));
            break;
        case RU_U8_E:
            lputc('E');
            break;
        case RU_U8_JO:
#ifdef ECONOMY_joe
            lputc('E');
#else
            lputc(loadSymbol(c, ru_JO));
#endif
            break;
        case RU_U8_ZH:
            lputc(loadSymbol(c, ru_ZH));
            break;
        case RU_U8_Z:
            lputc(loadSymbol(c, ru_Z));
            break;
        case RU_U8_I:
#ifdef ECONOMY_IN
            lputc('N');
#else
            lputc(loadSymbol(c, ru_I));
#endif
            break;
        case RU_U8_J:
#ifdef ECONOMY_ji
    #ifdef ECONOMY_IN
            lputc('N');
    #else
            lputc(loadSymbol(RU_U8_I, ru_I));
    #endif
#else
            lputc(loadSymbol(c, ru_J));
#endif
            break;
        case RU_U8_K:
            lputc('K');
            break;
        case RU_U8_L:
            lputc(loadSymbol(c, ru_L));
            break;
        case RU_U8_M:
            lputc('M');
            break;
        case RU_U8_N:
            lputc('H');
            break;
        case RU_U8_O:
            lputc('O');
            break;
        case RU_U8_P:
            lputc(loadSymbol(c, ru_P));
            break;
        case RU_U8_R:
            lputc('P');
            break;
        case RU_U8_S:
            lputc('C');
            break;
        case RU_U8_T:
            lputc('T');
            break;
        case RU_U8_U:
#ifdef ECONOMY_UY
            lputc('Y');
#else
            lputc(loadSymbol(c, ru_U));
#endif
            break;
        case RU_U8_F:
            lputc(loadSymbol(c, ru_F));
            break;
        case RU_U8_H:
            lputc('X');
            break;
        case RU_U8_C:
            lputc(loadSymbol(c, ru_C));
            break;
        case RU_U8_CH:
#ifdef ECONOMY_CH4
            lputc('4');
#else
            lputc(loadSymbol(c, ru_CH));
#endif
            break;
        case RU_U8_SH:
            lputc(loadSymbol(c, ru_SH));
            break;
        case RU_U8_SHH:
            lputc(loadSymbol(c, ru_SHH));
            break;
        case RU_U8_TZ:
#ifdef ECONOMY_tzmz
            lputc(loadSymbol(RU_U8_MZ, ru_MZ));
#else
            lputc(loadSymbol(c, ru_TZ));
#endif
            break;
        case RU_U8_Y:
            lputc(loadSymbol(c, ru_Y));
            break;
        case RU_U8_MZ:
            lputc(loadSymbol(c, ru_MZ));
            break;
        case RU_U8_EE:
            lputc(loadSymbol(c, ru_E));
            break;
        case RU_U8_JU:
            lputc(loadSymbol(c, ru_JU));
            break;
        case RU_U8_JA:
#ifdef ECONOMY_JAR
            lputc('R');
#else
            lputc(loadSymbol(c, ru_JA));
#endif
            break;
    }
}
#endif

void showImage(const uint8_t (*img)[8], uint16_t time_s)
{
    lcdPos(0,0);
    for(uint8_t i=0 ; i<16 ; ++i) {
        lputc(0x20);
    }
    lcdPos(0,1);
    for(uint8_t i=0 ; i<16 ; ++i) {
        lputc(0x20);
    }

    for(uint16_t time=0 ; time < time_s*6 ; ++time) {

        lcdPos(8,1);
        for(uint8_t i=0 ; i<8 ; ++i) {
            lputc(0x20);
        }
        for(uint8_t i=0 ; i<8 ; ++i) {
            lcdCustomSymbol(i,img[i]);
        }
        lcdPos(0,0);
        for(uint8_t i=0 ; i<8 ; ++i) {
            lputc(i);
        }
        delay_ms(35);

        lcdPos(0,0);
        for(uint8_t i=0 ; i<8 ; ++i) {
            lputc(0x20);
        }
        for(uint8_t i=0 ; i<8 ; ++i) {
            lcdCustomSymbol(i,img[i+8]);
        }
        lcdPos(8,0);
        for(uint8_t i=0 ; i<8 ; ++i) {
            lputc(i);
        }
        delay_ms(35);

        lcdPos(8,0);
        for(uint8_t i=0 ; i<8 ; ++i) {
            lputc(0x20);
        }
        for(uint8_t i=0 ; i<8 ; ++i) {
            lcdCustomSymbol(i,img[i+16]);
        }
        lcdPos(0,1);
        for(uint8_t i=0 ; i<8 ; ++i) {
            lputc(i);
        }
        delay_ms(35);

        lcdPos(0,1);
        for(uint8_t i=0 ; i<8 ; ++i) {
            lputc(0x20);
        }
        for(uint8_t i=0 ; i<8 ; ++i) {
            lcdCustomSymbol(i,img[i+24]);
        }
        lcdPos(8,1);
        for(uint8_t i=0 ; i<8 ; ++i) {
            lputc(i);
        }
        delay_ms(35);
    }
}
