
#include "../stm32/regs/tim_regs.h"
#include "../stm32/gpio.h"
#include "../stm32/delay.h"
//#include "../../stm32/usbcom_virtual/usbcom.h"
#include "../stm32/rcc.h"

#include "hd44780.h"
#include "pbm_to_symbols/img1602.h"

//extern uint8_t vcpRxBuffer[64];
void contrast(void);


void contrast()
{
    RCC_APB1ENR |= TIM2EN;
    GPIOA_CRL |= CNF_AF_PUSH_PULL(1) | MODE_OUTPUT50(1);
    TIM2_CR1  = CKD_CK_INT;
    TIM2_PSC  = 0x01;
    TIM2_ARR  = 10;
    TIM2_CCR2  = 3;
    TIM2_CCMR1 = OC2M_PWM1 | OC2PE;
    TIM2_CCER  = CC2E;
    TIM2_DIER = UIE;
    TIM2_EGR |= UG;
    TIM2_CR1 = CEN;
}

int main(void) {
    RCC_APB2ENR |= IOPAEN;
    gpioSetPushPull(GPIOA, GPIO1);

    lcdInit();

//    luputs("абвгдеёжзийклмно");
//    luputs("абвгдеёжзиорсух");
//    luputs("don't staay11");
//    luputs("dictator image");
    luputs("я ломал стекло");
//    luputs("Ура, скоро зима");

    lcdPos(0,1);
//    lprintf("прстуфх %d", -10);
//    luputs("прстуфхцчшщъыьэю");
//    luputs("Новый год");
//    lprintf("%d", -23);

    luputs("рюмка водки на с");
//    luputs("high voltage33");

    contrast();

//    showImage(segs, 1000);

    while(1){
        gpioSet(GPIOA, GPIO1);
        delay_ms(500);
        gpioReset(GPIOA, GPIO1);
        delay_ms(500);
    }
}
