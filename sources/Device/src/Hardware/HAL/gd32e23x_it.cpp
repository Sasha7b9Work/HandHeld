#include "defines.h"
#include "gd32e23x_it.h"
#include "systick.h"
#include "Display/Display.h"
#include "Modules/CMT2210AW/CMT2210AW.h"

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
}


void TIMER2_IRQHandler(void)
{
    static uint prev_time = 0;

    if (SET == timer_interrupt_flag_get(TIMER2, TIMER_INT_FLAG_UP))
    {
        /* clear channel 0 interrupt bit */
        timer_interrupt_flag_clear(TIMER2, TIMER_INT_FLAG_UP);

        uint time = timer_counter;

        Display::SetTimeInterrupt(time - prev_time);

        prev_time = time;

        CMT2210AW::CallbackOn1MS();
    }
}


#ifdef __cplusplus
}
#endif
