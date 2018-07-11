#include "spi.h"

uint8_t spi_read_reg(struct spiHandle_t* spi, uint8_t reg) {
	gpio_clear(spi->cs_port, spi->cs_pin);
	spi_xfer(spi->spi, reg | 0x80);
	uint8_t ret = spi_xfer(spi->spi, 0x00);
	gpio_set(spi->cs_port, spi->cs_pin);
	return ret;
}
uint8_t spi_read_reg_d(struct spiHandle_t* spi, uint8_t reg) {
	uint8_t ret = spi_read_reg(spi, reg);
	spi_delay();
	return ret;
}
void spi_write_reg(struct spiHandle_t* spi, uint8_t reg, uint8_t data){
	gpio_clear(spi->cs_port, spi->cs_pin);
	spi_xfer(spi->spi, reg);
	spi_xfer(spi->spi, data);
	gpio_set(spi->cs_port, spi->cs_pin);
}
void spi_write_reg_d(struct spiHandle_t* spi, uint8_t reg, uint8_t data){
	spi_write_reg(spi, reg, data);
    spi_delay();
}
uint16_t spi_read_reg16(struct spiHandle_t* spi, uint8_t reg){
	gpio_clear(spi->cs_port, spi->cs_pin);
	spi_xfer(spi->spi, reg | 0x80);
	uint16_t ret = spi_xfer(spi->spi, 0x00);
	ret = (ret<<8) | spi_xfer(spi->spi, 0x00);
	gpio_set(spi->cs_port, spi->cs_pin);
	return ret;
}
void spi_read_reg_burst(struct spiHandle_t* spi, uint8_t reg, int count, uint8_t* buf){
	gpio_clear(spi->cs_port, spi->cs_pin);
	spi_xfer(spi->spi, reg | 0x80);
	for(int i = 0; i < count; i++) {
		buf[i] = spi_xfer(spi->spi, 0x00);
	}
	gpio_set(spi->cs_port, spi->cs_pin);
}
void spi_modeFast(struct spiHandle_t* spi){
	spi_set_baudrate_prescaler(spi->spi, SPI_CR1_BR_FPCLK_DIV_8);
}
void spi_modeSlow(struct spiHandle_t* spi){
	spi_set_baudrate_prescaler(spi->spi, SPI_CR1_BR_FPCLK_DIV_128);
}
void spi_delay(){
	delayUS_DWT(4);
}
