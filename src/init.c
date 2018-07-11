#include <init.h>

unsigned long SystemCoreClock = 16000000UL;

void led_setup(void)
{
	rcc_periph_clock_enable(RCC_GPIOD);
	gpio_mode_setup(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO12 | GPIO13 | GPIO14 | GPIO15);

}
void spi_setup(void)
{
	rcc_periph_clock_enable(RCC_SPI1);
	rcc_periph_clock_enable(RCC_GPIOA);

	gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO4);
	gpio_set(GPIOA, GPIO4);

	gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO5 | GPIO6 | GPIO7);
	gpio_set_af(GPIOA, GPIO_AF5, GPIO5 | GPIO6 | GPIO7);

	spi_reset(SPI1);
	spi_set_master_mode(SPI1);
	spi_set_baudrate_prescaler(SPI1, SPI_CR1_BR_FPCLK_DIV_128);
	spi_set_clock_polarity_1(SPI1);
	spi_set_clock_phase_1(SPI1);
	spi_set_full_duplex_mode(SPI1);
	spi_set_unidirectional_mode(SPI1);
	spi_set_dff_8bit(SPI1);
	spi_enable_software_slave_management(SPI1);
	spi_send_msb_first(SPI1);
	spi_set_nss_high(SPI1);
	spi_enable(SPI1);
}
void clk_setup(void) {
	//rcc_clock_setup_hse_3v3(&rcc_hse_8mhz_3v3[RCC_CLOCK_3V3_168MHZ]);
	rcc_clock_setup_hse_3v3(&rcc_hse_8mhz_3v3[RCC_CLOCK_3V3_120MHZ]);
	SystemCoreClock = 120000000UL;
	dwt_enable_cycle_counter();
}
void exti_setup(void){
	rcc_periph_clock_enable(RCC_SYSCFG);
	rcc_periph_clock_enable(RCC_GPIOC);

    gpio_mode_setup(GPIOC, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO4);

	exti_enable_request(EXTI4);
	exti_select_source(EXTI4, GPIOC);
	exti_set_trigger(EXTI4, EXTI_TRIGGER_RISING);
    nvic_enable_irq(NVIC_EXTI4_IRQ);
}
