#ifndef H_HD44780_STUFF
#define H_HD44780_STUFF
/*
 * HD44780 2 line symbol display driver. Constants and codetables.
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

/** can't touch this (library relative constants) **/
/** Commands list **/
// Clears entire display and sets DDRAM address 0.
#define CLEAR_DISPLAY   0x01
// Sets DDRAM address 0 in 1.52 ms address counter.
#define RETURN_HOME     0x02
// Sets cursor move direction and specifies display shift.
#define ENTRY_MODE_SET  0x04
#define F_ID            0x02
#define F_S             0x01
// Sets displ (D) on/off, 37 μs cursor on/off (C), and blinking (B).
#define DISPLAY_ON      0x08
#define F_D             0x04
#define F_C             0x02
#define F_B             0x01
// Moves cursor and shifts display.
#define CURSOR_SHIFT    0x10
#define F_SC            0x08
#define F_RL            0x04
// Sets 8/4 bit iface (DL), num of lines (N), and font (F).
#define FUNCTION_SET    0x20
#define F_DL            0x10
#define F_N             0x08
#define F_F             0x04
// Sets CGRAM address.
#define SET_CGRAM_ADDR  0x40
#define ACG_MSK         0x3f
// Sets DDRAM address.
#define SET_DDRAM_ADDR  0x80
#define ADD_MSK         0x7f
// read busy flag and ddram addr.
#define BF              0x80
#define AC_MSK          0x7f
enum {
    WRITE_INTERNAL = 0,
    READ_BUSY,
    WRITE_RAM,
    READ_RAM
};
#define SECOND_STR_SFT  0x40
#define RAM_SIZE        8

/** Timings **/
#define BIT_DELAY_US        2
#define COMMAND_DELAY_US    50
#define SWON_DELAY_MS       16
#define SETBUS_DELAY_MS     1
#define CLRSCR_DELAY_MS     5

/** Codetables **/
#define ASCII_END       0x7a
// In order to get code for display for the russian letter.
// Decrease lower byte n by @RU_UTF_SHIFT and fetch nth byte from array ru_utf8.
#define RU_UTF_SHIFT    128
const uint8_t ru_utf8[64] = { 0x70, 0x63, 0xbf, 0x79, 0xe4, 0x78, 0xe5, 0xc0,\
                              0xc1, 0xe6, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7,\
                              0x41, 0xa0, 0x42, 0xa1, 0xe0, 0x45, 0xa3, 0xa4,\
                              0xa5, 0xa6, 0x4b, 0xa7, 0x4d, 0x48, 0x4f, 0xa8,\
                              0x50, 0x43, 0x54, 0xa9, 0xaa, 0x58, 0xe1, 0xab,\
                              0xac, 0xe2, 0xad, 0xae, 0x62, 0xaf, 0xb0, 0xb1,\
                              0x61, 0xb2, 0xb3, 0xb4, 0xe3, 0x65, 0xb6, 0xb7,\
                              0xb8, 0xb9, 0xba, 0xbb, 0xbc, 0xbd, 0x6f, 0xbe };
// But do not forget to check ё separately
#define RU_UTF_E_UP     0xd081
#define RU_UTF_E_LOW    0xd191
#define HD44780_E_UP    0xa2
#define HD44780_E_LOW   0xb5
// High byte for recognizing russian letters
#define RU_UTF_UPPER1   0xd0
#define RU_UTF_UPPER2   0xd1

#define CUSTOM_SYMBOLS_NUMBER   8

#endif
