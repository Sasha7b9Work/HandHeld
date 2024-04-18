// 2024/04/18 15:19:44 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/HAL/HAL.h"
#include "Modules/ST7735/ST7735.h"
#include "Modules/CMT2210AW/CMT2210AW.h"
#include "Hardware/HAL/systick.h"
#include <gd32e23x.h>


ModeClock::E ModeClock::current = ModeClock::Low;


namespace HAL_CLOCK
{
    static void SetDeepSleep();
    static void SetLow();
    static void SetHi();

    static bool in_sleep_mode = false;
}


void ModeClock::Set(E v)
{
    current = v;

    if (v == ModeClock::DeepSleep)
    {
        HAL_CLOCK::in_sleep_mode = true;

        HAL_CLOCK::SetDeepSleep();
    }
    else if (v == ModeClock::Low)
    {
        HAL_CLOCK::SetLow();
    }
    else if (v == ModeClock::Hi)
    {
        HAL_CLOCK::SetHi();
    }
}


void ModeClock::LeaveDeepSleep()
{
    if (HAL_CLOCK::in_sleep_mode)
    {
        HAL_CLOCK::in_sleep_mode = false;

        ModeClock::Set(ModeClock::Low);
    }
}


void HAL_CLOCK::SetDeepSleep()
{
    ST7735::Disable();

    CMT2210AW::PrepareToSleep();

    /* AHB = SYSCLK */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
    /* APB2 = AHB */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV1;
    /* APB1 = AHB */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV1;

    /* select IRC8M as system clock */
    RCU_CFG0 &= ~RCU_CFG0_SCS;
    RCU_CFG0 |= RCU_CKSYSSRC_IRC8M;

    /* wait until IRC8M is selected as system clock */
    while (RCU_SCSS_IRC8M != (RCU_CFG0 & RCU_CFG0_SCSS)) {
    }

    rcu_periph_clock_enable(RCU_PMU);
    pmu_to_deepsleepmode(PMU_LDO_LOWPOWER, WFI_CMD);
}


void HAL_CLOCK::SetLow()
{
    SystemCoreClock = 3250000;

    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;

    /* enable HXTAL */
    RCU_CTL0 |= RCU_CTL0_HXTALEN;

    /* wait until HXTAL is stable or the startup time is longer than HXTAL_STARTUP_TIMEOUT */
    do {
        timeout++;
        stab_flag = (RCU_CTL0 & RCU_CTL0_HXTALSTB);
    } while ((0U == stab_flag) && (HXTAL_STARTUP_TIMEOUT != timeout));
    /* if fail */
    if (0U == (RCU_CTL0 & RCU_CTL0_HXTALSTB)) {
        while (1) {
        }
    }

    FMC_WS = (FMC_WS & (~FMC_WS_WSCNT)) | WS_WSCNT_2;

    /* HXTAL is stable */
    /* AHB = SYSCLK */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
    /* APB2 = AHB */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV1;
    /* APB1 = AHB */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV1;

    /* PLL = HXTAL * 3 = 78 MHz */
    RCU_CFG0 &= ~(RCU_CFG0_PLLSEL | RCU_CFG0_PLLMF | RCU_CFG0_PLLDV);
    RCU_CFG0 |= (RCU_PLLSRC_HXTAL | RCU_PLL_MUL2);

    rcu_hxtal_prediv_config(RCU_PLL_PREDV16);
    RCU_CFG0 |= RCU_CFG0_PLLDV;         // Должно быть то же, что и в PREDV2[0]

    /* enable PLL */
    RCU_CTL0 |= RCU_CTL0_PLLEN;

    /* wait until PLL is stable */
    while (0U == (RCU_CTL0 & RCU_CTL0_PLLSTB)) {
    }

    /* select PLL as system clock */
    RCU_CFG0 &= ~RCU_CFG0_SCS;
    RCU_CFG0 |= RCU_CKSYSSRC_PLL;

    /* wait until PLL is selected as system clock */
    while (RCU_SCSS_PLL != (RCU_CFG0 & RCU_CFG0_SCSS)) {
    }

    systick_config();
}


void HAL_CLOCK::SetHi()
{
    SystemCoreClock = 52000000;

    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;

    /* enable HXTAL */
    RCU_CTL0 |= RCU_CTL0_HXTALEN;

    /* wait until HXTAL is stable or the startup time is longer than HXTAL_STARTUP_TIMEOUT */
    do {
        timeout++;
        stab_flag = (RCU_CTL0 & RCU_CTL0_HXTALSTB);
    } while ((0U == stab_flag) && (HXTAL_STARTUP_TIMEOUT != timeout));
    /* if fail */
    if (0U == (RCU_CTL0 & RCU_CTL0_HXTALSTB)) {
        while (1) {
        }
    }

    FMC_WS = (FMC_WS & (~FMC_WS_WSCNT)) | WS_WSCNT_2;

    /* HXTAL is stable */
    /* AHB = SYSCLK */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
    /* APB2 = AHB */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV1;
    /* APB1 = AHB */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV1;

    /* PLL = HXTAL * 3 = 78 MHz */
    RCU_CFG0 &= ~(RCU_CFG0_PLLSEL | RCU_CFG0_PLLMF | RCU_CFG0_PLLDV);
    RCU_CFG0 |= (RCU_PLLSRC_HXTAL | RCU_PLL_MUL2);

    /* enable PLL */
    RCU_CTL0 |= RCU_CTL0_PLLEN;

    /* wait until PLL is stable */
    while (0U == (RCU_CTL0 & RCU_CTL0_PLLSTB)) {
    }

    /* select PLL as system clock */
    RCU_CFG0 &= ~RCU_CFG0_SCS;
    RCU_CFG0 |= RCU_CKSYSSRC_PLL;

    /* wait until PLL is selected as system clock */
    while (RCU_SCSS_PLL != (RCU_CFG0 & RCU_CFG0_SCSS)) {
    }

    systick_config();
}
