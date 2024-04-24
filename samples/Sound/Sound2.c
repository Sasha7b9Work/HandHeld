//***************************************************************************
//  Author(s)...: Chiper 
//  URL.........: digitalchip.ru
//
//  Device(s)...: ATMega8 (4MHz)
//  Description.: Music box 
//***************************************************************************

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "melody.h"


#define DEBOUNCE_TIME 25        // Задержка для подавления дребезга кнопки

#define BUTTON_PORT PORTD       // Порт для кнопки 
#define BUTTON_PIN 	PIND         
#define BUTTON_DDR 	DDRD         
#define BUTTON_BIT 	7           // Номер пина, к которому подключена нопка

//Таблицы частот нот и длительностей
unsigned int  notefreq[] PROGMEM = {0,4748,4480,4228,3992,3768,3556,3356,3168,2990,2822,2664,2514,2374,2240,2114,1996,1884,1778,1678,1584,1495,1411,1332,1257,1187,1120,1057,998,942,889,839,792};
unsigned int  pausedelay[] PROGMEM = {32,64,128,256,512,1024,2048,4096};

// Своя задержка, так как _delay_ms на вход принимает только константу
void delay_note (unsigned int delay)
{	
	for (int i=0; i< delay; i++) _delay_ms(1);
}

// Определяем нажатие кнопки. Возвращает: 1 - нажата, 0 - не нажата
int button_is_pressed()
{
	// Кнопка нажата, если BUTTON_BIT = 0
	if (bit_is_clear(BUTTON_PIN, BUTTON_BIT))
	{
    	_delay_ms(DEBOUNCE_TIME); // Задержка на время дребезга
		
		// Повтороно считываем состояние кнопки
        if (bit_is_clear(BUTTON_PIN, BUTTON_BIT)) return 1;
    }
    return 0;
}

//***************************************************************************
// Инициализация
void avr_init()
{
	TCCR1A=0x00;
	TCCR1B=0x09;
	
	DDRB  |=  _BV(PB1); // Включаем нужный пин на выход
	PORTB &= ~_BV(PB1); // Устанавливаем в 0
    
	BUTTON_DDR &= ~_BV(BUTTON_BIT);   // Включаем нужный пин на вход
	BUTTON_PORT |= _BV(BUTTON_BIT);   // Включаем подтягивающий резистор для кнопки
}


//***************************************************************************
int main (void)
{
	unsigned char freqnote;		// Код ноты
	unsigned char delaynote;	// Код длительности
	unsigned char tmp;			// Временная переменная
	

	avr_init();		// Инициализируем периферию

	while(1)		// Главный цикл
	{
		
		if (button_is_pressed())
		{		
			int cnt=0;	// На начало мелодии
			while ((tmp=pgm_read_byte(&(melody[cnt])))!=0)
			{
				freqnote = tmp&0x1F;		// Код ноты
				delaynote = (tmp>>5)&0x07;	// Код длительности
			
				if (freqnote!=0)			// Если не пауза
				{							// включаем звук
					OCR1A=pgm_read_word(&(notefreq[freqnote]));
					TCCR1A=0x40;
				}

				delay_note(pgm_read_word(&(pausedelay[delaynote]))); // выдерживаем длительность ноты
				TCCR1A=0x00; 	//выключаем звук
				delay_note(8); 	//выдерживаем паузу
								//чтоб две ноты не сливались в одну

				cnt++;		// Следующая нота
			} //while 		
		} // if button pressed

	}//End main loop
} 
