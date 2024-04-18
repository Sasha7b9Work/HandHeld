// 2023/5/8 19:15:35 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/HAL/HAL.h"
#include "Hardware/HAL/HAL_PINS.h"
#include "Hardware/Timer.h"
#include "Settings/Settings.h"
#include <gd32e23x.h>


#define I2C_SPEED              100000
#define I2C_SLAVE_ADDRESS7     (0xa2)   // ��� �����
#define I2C_PAGE_SIZE           8


namespace HAL_I2C
{
    static const uint TIMEOUT = 100;

    static bool WaitFlagYes(i2c_flag_enum);
    static bool WaitFlagNo(i2c_flag_enum);
}


bool HAL_I2C::WaitFlagYes(i2c_flag_enum flag)
{
    TimeMeterMS meter;

    while (i2c_flag_get(I2C_ADDR, flag))
    {
        if (meter.ElapsedTime() > TIMEOUT)
        {
            return false;
        }
    }

    return true;
}


bool HAL_I2C::WaitFlagNo(i2c_flag_enum flag)
{
    TimeMeterMS meter;

    while (!i2c_flag_get(I2C_ADDR, flag))
    {
        if (meter.ElapsedTime() > TIMEOUT)
        {
            return false;
        }
    }

    return true;
}


void HAL_I2C::Init()
{
    // SCL PB10 21 - alternate I2C1
    // SDA PB11 22 - alternate I2C1

    gpio_af_set(GPIOB, GPIO_AF_1, GPIO_PIN_10);
    gpio_af_set(GPIOB, GPIO_AF_1, GPIO_PIN_11);

    gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_10);
    gpio_output_options_set(GPIOB, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ, GPIO_PIN_10);

    gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_11);
    gpio_output_options_set(GPIOB, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ, GPIO_PIN_11);

    /* configure I2C clock */
    i2c_clock_config(I2C_ADDR, I2C_SPEED, I2C_DTCY_2);

    /* configure I2C address */
    i2c_mode_addr_config(I2C_ADDR, I2C_I2CMODE_ENABLE, I2C_ADDFORMAT_7BITS, I2C_SLAVE_ADDRESS7);

    /* enable I2C_ADDR */
    i2c_enable(I2C_ADDR);

    /* enable acknowledge */
    i2c_ack_config(I2C_ADDR, I2C_ACK_ENABLE);
}


bool HAL_I2C::Write(uint8 command, uint8 *data, int size)
{
    TimeMeterMS meter;

    /* wait until I2C bus is idle */
    if (!WaitFlagYes(I2C_FLAG_I2CBSY))
    {
        return false;
    }

    /* send a start condition to I2C bus */
    i2c_start_on_bus(I2C_ADDR);

    /* wait until SBSEND bit is set */
    if (!WaitFlagNo(I2C_FLAG_SBSEND))
    {
        return false;
    }

    /* send slave address to I2C bus */
    i2c_master_addressing(I2C_ADDR, I2C_SLAVE_ADDRESS7, I2C_TRANSMITTER);

    /* wait until ADDSEND bit is set */
    WaitFlagNo(I2C_FLAG_ADDSEND);

    /* N=1,reset ACKEN bit before clearing ADDRSEND bit */
    i2c_ack_config(I2C_ADDR, I2C_ACK_DISABLE);

    /* clear ADDSEND bit */
    i2c_flag_clear(I2C_ADDR, I2C_FLAG_ADDSEND);

    /* send command */
    i2c_data_transmit(I2C_ADDR, command);

    /* wait until the TBE bit is set */
    WaitFlagNo(I2C_FLAG_TBE);

    bool result = true;

    /* send array of data */
    for (int i = 0; i < size; i++)
    {
        i2c_data_transmit(I2C_ADDR, *data++);

        /* wait until the TBE bit is set */
        if (!WaitFlagNo(I2C_FLAG_TBE))
        {
            result = false;

            break;
        }
    }

    /* send a stop condition to I2C bus */
    i2c_stop_on_bus(I2C_ADDR);

    /* wait until stop condition generate */
    while (I2C_CTL0(I2C_ADDR) & 0x0200)
    {
        if (meter.ElapsedTime() > TIMEOUT)
        {
            result = false;

            break;
        }
    }

    /* Enable Acknowledge */
    i2c_ack_config(I2C_ADDR, I2C_ACK_ENABLE);

    return result;
}


bool HAL_I2C::Read(uint8 reg, uint8 *buf, uint16 len)
{
    TimeMeterMS meter;

    bool result = true;

    i2c_stop_on_bus(I2C_ADDR);

    /* wait until I2C bus is idle */
    WaitFlagYes(I2C_FLAG_I2CBSY);

    /* send a start condition to I2C bus */
    i2c_start_on_bus(I2C_ADDR);

    /* wait until SBSEND bit is set */
    WaitFlagNo(I2C_FLAG_SBSEND);

    /* send slave address to I2C bus */
    i2c_master_addressing(I2C_ADDR, I2C_SLAVE_ADDRESS7, I2C_TRANSMITTER);

    /* wait until ADDSEND bit is set */
    WaitFlagNo(I2C_FLAG_ADDSEND);

    /* clear ADDSEND bit */
    i2c_flag_clear(I2C_ADDR, I2C_FLAG_ADDSEND);

    /* send command */
    i2c_data_transmit(I2C_ADDR, reg);

    WaitFlagNo(I2C_FLAG_TBE);

    i2c_start_on_bus(I2C_ADDR);

    WaitFlagNo(I2C_FLAG_SBSEND);

    i2c_master_addressing(I2C_ADDR, I2C_SLAVE_ADDRESS7, I2C_RECEIVER);

    WaitFlagNo(I2C_FLAG_ADDSEND);

    i2c_flag_clear(I2C_ADDR, I2C_FLAG_ADDSEND);

    if (len == 1)
    {
        i2c_ack_config(I2C_ADDR, I2C_ACK_DISABLE);

        i2c_stop_on_bus(I2C_ADDR);

        while (!i2c_flag_get(I2C_ADDR, I2C_FLAG_RBNE))
        {
            if (meter.ElapsedTime() > TIMEOUT)
            {
                result = false;
                break;
            }
        }

        buf[0] = i2c_data_receive(I2C_ADDR);
    }
    else
    {
        for (int i = 0; i < len; i++)
        {
            if (i == len - 1)
            {
                i2c_ack_config(I2C_ADDR, I2C_ACK_DISABLE);
                i2c_stop_on_bus(I2C_ADDR);
            }

            while (!i2c_flag_get(I2C_ADDR, I2C_FLAG_RBNE))
            {
                if (meter.ElapsedTime() > TIMEOUT)
                {
                    result = false;
                    break;
                }
            }

            buf[i] = i2c_data_receive(I2C_ADDR);
        }
    }

    /* send a stop condition to I2C bus */
    i2c_stop_on_bus(I2C_ADDR);

    /* wait until stop condition generate */
    while (I2C_CTL0(I2C_ADDR) & 0x0200)
    {
        if (meter.ElapsedTime() > TIMEOUT)
        {
            result = false;
            break;
        }
    }

    /* enable acknowledge */
    i2c_ack_config(I2C_ADDR, I2C_ACK_ENABLE);

    return result;
}
