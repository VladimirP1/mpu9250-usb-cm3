#pragma once
#include <libopencm3/cm3/cortex.h>
#include <libopencm3/cm3/dwt.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/spi.h>
#include <libopencm3/stm32/exti.h>
#include <libopencm3/cm3/nvic.h>


extern unsigned long SystemCoreClock;

void led_setup(void);
void spi_setup(void);
void clk_setup(void);
void exti_setup(void);

