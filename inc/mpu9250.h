#pragma once
#include "spi.h"
#include "usb.h"
#include "comms.h"

void mpuTask(struct spiHandle_t spi);
void mpu_init(struct spiHandle_t* spi);
void mpu_reset_fifo(struct spiHandle_t* spi);
void mpu_run(struct spiHandle_t* spi);
uint16_t mpu_count(struct spiHandle_t* spi);
void mpu_sendusb(uint8_t* data);
