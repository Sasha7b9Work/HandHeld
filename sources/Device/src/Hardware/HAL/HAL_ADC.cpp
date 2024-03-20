// 2024/03/20 09:21:40 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/HAL/HAL.h"
#include "Hardware/Timer.h"
#include <gd32e23x.h>


namespace HAL_ADC
{
    static float voltage = 0.0f;

    static float ConversionRawToVoltageADC(uint);

    static float ConversionVoltageADCtoVoltageBattery(float);

    static float ConversionRawToVoltageBattery(uint);
}


void HAL_ADC::Init()
{
    rcu_periph_clock_enable(RCU_ADC);

    rcu_adc_clock_config(RCU_ADCCK_APB2_DIV6);

    gpio_mode_set(GPIOA, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO_PIN_1);

    /* ADC contineous function enable */
    adc_special_function_config(ADC_CONTINUOUS_MODE, ENABLE);
    /* ADC trigger config */
    adc_external_trigger_source_config(ADC_REGULAR_CHANNEL, ADC_EXTTRIG_REGULAR_NONE);
    /* ADC data alignment config */
    adc_data_alignment_config(ADC_DATAALIGN_RIGHT);
    /* ADC channel length config */
    adc_channel_length_config(ADC_REGULAR_CHANNEL, 1U);

    /* ADC regular channel config */
    adc_regular_channel_config(0U, ADC_CHANNEL_1, ADC_SAMPLETIME_55POINT5);
    adc_external_trigger_config(ADC_REGULAR_CHANNEL, ENABLE);

    /* ADC resolusion 6B */
    adc_resolution_config(ADC_RESOLUTION_6B);

    /* enable ADC interface */
    adc_enable();
    Timer::Delay(1U);
    /* ADC calibration and reset calibration */
    adc_calibration_enable();
}


float HAL_ADC::GetVoltage()
{
    adc_software_trigger_enable(ADC_REGULAR_CHANNEL);

    adc_flag_clear(ADC_FLAG_EOC);

    while (SET != adc_flag_get(ADC_FLAG_EOC)) { }

    voltage = ConversionRawToVoltageBattery(ADC_RDATA);

    return voltage;
}


float HAL_ADC::ConversionRawToVoltageADC(uint raw)
{
    static const float MAX_VOLTAGE = 3.0f;

    return MAX_VOLTAGE / (1 << 12) * (float)raw;
}


float HAL_ADC::ConversionVoltageADCtoVoltageBattery(float adc)
{
    return -0.6f * adc + 4.36f;
}


float HAL_ADC::ConversionRawToVoltageBattery(uint raw)
{
    float voltageADC = ConversionRawToVoltageADC(raw);

    return ConversionVoltageADCtoVoltageBattery(voltageADC) * 2.0f;
}