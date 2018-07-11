#pragma once
#include "usb.h"
#include "mpu9250.h"
#include <string.h>

struct params_t{
    int16_t acc_ofsx;
    int16_t acc_ofsy;
    int16_t acc_ofsz;
    int16_t gyr_ofsx;
    int16_t gyr_ofsy;
    int16_t gyr_ofsz;
};
extern struct params_t params;

extern uint8_t if_started;

void comms_init(usbd_device * usb);
void comms_new_sample(uint8_t* buf);
enum usbd_request_return_codes hid_control_request_class(usbd_device *dev, struct usb_setup_data *req, uint8_t **buf, uint16_t *len,
			void (**complete)(usbd_device *dev, struct usb_setup_data *req));
void tx_callback(usbd_device *usbd_dev, uint8_t ep);
