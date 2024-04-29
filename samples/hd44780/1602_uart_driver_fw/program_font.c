/*
 * HD44780 symbol display driver. New alphabet functions.
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

uint8_t newCodeTable[PAGE_SIZE] = {0};
uint8_t displayBackup[PAGE_NUM][LCD_SIZE*2] = {0x20};
uint8_t codeTableSize;

void garbageCollector(uint8_t pos);

void appendCyrillic(uint8_t code)
{
    // find the same
    for(uint8_t i=0 ; i<pageSize ; ++i) {
        if(newCodeTable[i] == code) {
            displayBackup[i/8][BPOS(posx,posy)] = i;
            return;
        }
    }
    // delete previous (if any)
    garbageCollector(BPOS(posx,posy));
    // add new one
    if(pageSize >= PAGE_SIZE-1) {
        return;
    }
    newCodeTable[pageSize] = code;
    displayBackup[pageSize/8][BPOS(posx,posy)] = pageSize;
    pageSize++;
}

void garbageCollector(uint8_t pos)
{
    // find the page of previous symbol
    uint8_t prevNewSymbolPage = PAGE_NUM+1;
    for(uint8_t i=0 ; i<pageSize/8 ; ++i) {
        if(displayBackup[i][pos] != 0x20) {
            prevNewSymbolPage = i;
        }
    }
    if(prevNewSymbolPage > PAGE_NUM) {
        return;
    }
    // check, if previous symbol occurs twice
    for(uint8_t i=0 ; i<LCD_SIZE*2 ; ++i) {
        if((displayBackup[prevNewSymbolPage][i] == displayBackup[prevNewSymbolPage][pos]) && (i != pos) {
            return;
        }
    }
    // find the previous symbol in the codetable
    uint8_t ptr;
    for(ptr=prevNewSymbolPage*8 ; ptr<pageSize ; ++ptr) {
        if(newCodeTable[ptr] == displayBackup[prevNewSymbolPage][pos]) {
            break;
        }
    }
    // delete the previous symbol from the codetable
    --pageSize;
    for( ; ptr<pageSize ; ++ptr ) {
        newCodeTable[ptr] = newCodeTable[ptr+1];
    }
    // delete the previous symbol from backup
    displayBackup[prevNewSymbolPage][pos] = 0x20;
}

void pageSwitch()
{
    static page = 0;
    for(uint8_t i=0 ; i<8 ; ++i) {
        lcdCustomSymbol(i,pointerTable[newCodeTable[(page*8)+i]]);
    }
    uint8_t prev;
    for(int i=0 ; i<LCD_SIZE ; ++i) {
        if((displayBackup[page][i] != 0x20) && (prev == i-1)) {
            lcdWriteRamm(displayBackup[page][i]-(page*8));
            prev=i;
        } else if(displayBackup[page][i] != 0x20) {
            lcdCommand(SET_DDRAM_ADDR | i);
            lcdWriteRamm(displayBackup[page][i]-(page*8));
            prev=i;
        }
    }
    for(int i=LCD_SIZE ; i<LCD_SIZE*2 ; ++i) {
        if((displayBackup[page][i] != 0x20) && (prev == i-1)) {
            lcdWriteRamm(displayBackup[page][i]-(page*8));
            prev=i;
        } else if(displayBackup[page][i] != 0x20) {
            lcdCommand(SET_DDRAM_ADDR | i+24);
            lcdWriteRamm(displayBackup[page][i]-(page*8));
            prev=i;
        }
    }
    ++page;
    if(page*8 > pageSize)
}
