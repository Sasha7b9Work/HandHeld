#include "defines.h"
#include "gd32e23x_it.h"
#include "systick.h"


#ifdef __cplusplus
extern "C" {
#endif


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
    delay_decrement();
}


// PB0 LEFT
// PB1 DOWN
void EXTI0_1_IRQHandler(void)
{
    if (SET == exti_interrupt_flag_get(EXTI_0))
    {
        exti_interrupt_flag_clear(EXTI_0);
    }

    if (SET == exti_interrupt_flag_get(EXTI_1))
    {
        exti_interrupt_flag_clear(EXTI_1);
    }
}

// PB2 RIGHT
void EXTI2_3_IRQHandler(void)
{
    if (SET == exti_interrupt_flag_get(EXTI_2))
    {
        exti_interrupt_flag_clear(EXTI_2);
    }
}


// PA7 UP
void EXTI4_15_IRQHandler(void)
{
    if (SET == exti_interrupt_flag_get(EXTI_7))
    {
        exti_interrupt_flag_clear(EXTI_7);
    }
}


#ifdef __cplusplus
}
#endif