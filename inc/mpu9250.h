#pragma once
#include "spi.h"
#include "usb.h"
#include "comms.h"

#define BUF_SET_TIME(buf, time) \
    buf[12] = time >> 24; \
    buf[13] = time >> 16; \
	buf[14] = time >> 8; \
	buf[15] = time;

void mpu_start(struct spiHandle_t *spi);
void mpu_getsample();

