#pragma once
#include "spi.h"
#include "usb.h"
#include "comms.h"

#define BUF_SET_TIME(buf, time, offset) \
    (buf)[0 + offset] = (time) >> 24; \
    (buf)[1 + offset] = (time) >> 16; \
	(buf)[2 + offset] = (time) >> 8; \
	(buf)[3 + offset] = (time);

void mpu_start(struct spiHandle_t *spi);
void mpu_getsample();

