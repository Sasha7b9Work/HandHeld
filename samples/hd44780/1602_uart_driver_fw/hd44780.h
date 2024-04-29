#ifndef H_HD44780
#define H_HD44780
/*
 * HD44780 2 line symbol display driver.
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
#include <inttypes.h>
#include "../stm32/gpio.h"

/** Pins and port definitions **/
// instructions or data select pin (1 is data)
#define RS_PIN      GPIO2
#define RS_PORT     GPIOA
// selects read or write (1 is read)
#define RW_PIN      GPIO1
#define RW_PORT     GPIOA
// starting data read/write operations (1 enables bus)
#define E_PIN       GPIO3
#define E_PORT      GPIOA
// data bus
#define D4_PIN      GPIO4
#define D5_PIN      GPIO5
#define D6_PIN      GPIO6
#define D7_PIN      GPIO7
#define D0_PIN      D7_PIN
#define D1_PIN      D7_PIN
#define D2_PIN      D7_PIN
#define D3_PIN      D7_PIN
#define DATA_PORT   GPIOA
/** not typical case **/
#define D0_PORT DATA_PORT
#define D1_PORT DATA_PORT
#define D2_PORT DATA_PORT
#define D3_PORT DATA_PORT
#define D4_PORT DATA_PORT
#define D5_PORT DATA_PORT
#define D6_PORT DATA_PORT
#define D7_PORT DATA_PORT

/** display config **/
// uncomment your bus size
//#define LCD_4BIT
#define LCD_8BIT
// set display size
#define LCD_SIZE    16
// could you use RW pin ?
//#define RW_DISABLE
// program russian alphabet (if there isn't any normal)
#define PROGRAM_RU

enum {
    CURSOR_OFF = 0,
    CURSOR_UNDERSCORE,
    CURSOR_UNDERSCORE_BLINK,
    CURSOR_BLINK
};

void lcdInit(void);
void lcdClr(void);
void lcdCursor(uint8_t state);
void lcdPos(uint8_t x, uint8_t y);
void lputc(char c);
void lputs(char *c);
void luputs(char *c);
void lprintf(char *format, ... );
void lcdCustomSymbol(uint8_t code, const uint8_t *symbol);
void showImage(const uint8_t (*img)[8], uint16_t time_s);

#endif
