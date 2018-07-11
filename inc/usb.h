#pragma once
#include "init.h"
#include <stdlib.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/spi.h>
#include <libopencm3/usb/dwc/otg_fs.h>
#include <libopencm3/usb/usbd.h>
#include <libopencm3/usb/hid.h>
#include "comms.h"

#define USB_REQ_GET_REPORT 1
#define USB_REQ_SET_REPORT 9
#define USB_VAL_IS_FEATURE(x) ((x & 0xff00) == 0x0300)


extern uint8_t usbd_control_buffer[128];
usbd_device * usb_init(void);
