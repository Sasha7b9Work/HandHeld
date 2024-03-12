#include "defines.h"
#include "gd32e23x_it.h"
#include "systick.h"
#include "Display/Display.h"
#include "Modules/CMT2210AW/CMT2210AW.h"
#include "Keyboard/Keyboard.h"


#ifdef __cplusplus
extern "C" {
#endif


extern uint timer_counter;


/*!
    \brief      this function handles NMI exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void NMI_Handler(void)
{
}

/*!
    \brief      this function handles HardFault exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void HardFault_Handler(void)
{
    /* if Hard Fault exception occurs, go to infinite loop */
    while(1){
    }
}

/*!
    \brief      this function handles SVC exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void SVC_Handler(void)
{
}

/*!
    \brief      this function handles PendSV exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void PendSV_Handler(void)
{
}

/*!
    \brief      this function handles SysTick exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void SysTick_Handler(void)
{
    timer_counter++;

    delay_decrement();

    Keyboard::Update();
}


void EXTI4_15_IRQHandler(void)
{
    if (RESET != exti_interrupt_flag_get(EXTI_13))
    {
        exti_interrupt_flag_clear(EXTI_13);

        CMT2210AW::CallbackOnStartSCK();
    }
}


void TIMER2_IRQHandler(void)
{
    static uint d_time = 0;
    static uint counter = 0;
    static uint time_start = timer_counter;

    if (SET == timer_interrupt_flag_get(TIMER2, TIMER_INT_FLAG_UP))
    {
        if (counter++ == 10000)
        {
            d_time = timer_counter - time_start;
            counter = 0;
            time_start = timer_counter;
        }

        CMT2210AW::CallbackOn1MS();

        /* clear channel 0 interrupt bit */
        timer_interrupt_flag_clear(TIMER2, TIMER_INT_FLAG_UP);
    }
}


#ifdef __cplusplus
}
#endif
