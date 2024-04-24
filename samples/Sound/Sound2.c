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


#define DEBOUNCE_TIME 25        // �������� ��� ���������� �������� ������

#define BUTTON_PORT PORTD       // ���� ��� ������ 
#define BUTTON_PIN 	PIND         
#define BUTTON_DDR 	DDRD         
#define BUTTON_BIT 	7           // ����� ����, � �������� ���������� �����

//������� ������ ��� � �������������
unsigned int  notefreq[] PROGMEM = {0,4748,4480,4228,3992,3768,3556,3356,3168,2990,2822,2664,2514,2374,2240,2114,1996,1884,1778,1678,1584,1495,1411,1332,1257,1187,1120,1057,998,942,889,839,792};
unsigned int  pausedelay[] PROGMEM = {32,64,128,256,512,1024,2048,4096};

// ���� ��������, ��� ��� _delay_ms �� ���� ��������� ������ ���������
void delay_note (unsigned int delay)
{	
	for (int i=0; i< delay; i++) _delay_ms(1);
}

// ���������� ������� ������. ����������: 1 - ������, 0 - �� ������
int button_is_pressed()
{
	// ������ ������, ���� BUTTON_BIT = 0
	if (bit_is_clear(BUTTON_PIN, BUTTON_BIT))
	{
    	_delay_ms(DEBOUNCE_TIME); // �������� �� ����� ��������
		
		// ��������� ��������� ��������� ������
        if (bit_is_clear(BUTTON_PIN, BUTTON_BIT)) return 1;
    }
    return 0;
}

//***************************************************************************
// �������������
void avr_init()
{
	TCCR1A=0x00;
	TCCR1B=0x09;
	
	DDRB  |=  _BV(PB1); // �������� ������ ��� �� �����
	PORTB &= ~_BV(PB1); // ������������� � 0
    
	BUTTON_DDR &= ~_BV(BUTTON_BIT);   // �������� ������ ��� �� ����
	BUTTON_PORT |= _BV(BUTTON_BIT);   // �������� ������������� �������� ��� ������
}


//***************************************************************************
int main (void)
{
	unsigned char freqnote;		// ��� ����
	unsigned char delaynote;	// ��� ������������
	unsigned char tmp;			// ��������� ����������
	

	avr_init();		// �������������� ���������

	while(1)		// ������� ����
	{
		
		if (button_is_pressed())
		{		
			int cnt=0;	// �� ������ �������
			while ((tmp=pgm_read_byte(&(melody[cnt])))!=0)
			{
				freqnote = tmp&0x1F;		// ��� ����
				delaynote = (tmp>>5)&0x07;	// ��� ������������
			
				if (freqnote!=0)			// ���� �� �����
				{							// �������� ����
					OCR1A=pgm_read_word(&(notefreq[freqnote]));
					TCCR1A=0x40;
				}

				delay_note(pgm_read_word(&(pausedelay[delaynote]))); // ����������� ������������ ����
				TCCR1A=0x00; 	//��������� ����
				delay_note(8); 	//����������� �����
								//���� ��� ���� �� ��������� � ����

				cnt++;		// ��������� ����
			} //while 		
		} // if button pressed

	}//End main loop
} 
