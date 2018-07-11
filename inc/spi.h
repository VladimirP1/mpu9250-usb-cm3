#pragma once
#include "util.h"

struct spiHandle_t {
	uint32_t spi;
	uint32_t cs_port;
	uint16_t cs_pin;
};
uint8_t spi_transfer(struct spiHandle_t* spi, uint8_t byte);
uint8_t spi_read_reg(struct spiHandle_t* spi, uint8_t reg);
uint8_t spi_read_reg_d(struct spiHandle_t* spi, uint8_t reg);
void spi_write_reg(struct spiHandle_t* spi, uint8_t reg, uint8_t data);
void spi_write_reg_d(struct spiHandle_t* spi, uint8_t reg, uint8_t data);

uint16_t spi_read_reg16(struct spiHandle_t* spi, uint8_t reg);
void spi_read_reg_burst(struct spiHandle_t* spi, uint8_t reg, int count, uint8_t* buf);

void spi_modeFast(struct spiHandle_t* spi);
void spi_modeSlow(struct spiHandle_t* spi);

void spi_delay();
void spi_delay_us(int us);

