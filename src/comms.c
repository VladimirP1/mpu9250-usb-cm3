#include <comms.h>
#include <staticqueue.inl>

usbd_device * usb;
struct params_t params;

//void apply_offsets(int16_t* buf);

void comms_init(usbd_device * usbd){
	usb = usbd;
	memset(&params, 0, sizeof(struct params_t));
	//usbd_ep_write_packet(usb, 0x81, simq.buf, 32);
}

// From here we get notified of new data
// So we need to read it out
void exti4_isr(){
	exti_reset_request(EXTI4);
	gpio_toggle(GPIOD, GPIO14);
	mpu_getsample();
	gpio_clear(GPIOD, GPIO13);
}

// Data has been read out, push it into FIFO
void comms_new_sample(uint8_t* buf){
	//apply_offsets((int16_t*) buf);
	cm_disable_interrupts();
	push(buf);
	cm_enable_interrupts();
}

// Data has been transmitted, transmit new data
void tx_callback(usbd_device *usbd_dev, uint8_t ep){
	static uint8_t localbuf[32];
	gpio_set(GPIOD, GPIO13);
	memset(localbuf, 0, 32);
	cm_disable_interrupts();
	pop(localbuf);
	pop(localbuf + 16);
	cm_enable_interrupts();
	usbd_ep_write_packet(usb, 0x81, localbuf, 32);
}

// Handle GET_REPORT and SET_REPORT
enum usbd_request_return_codes hid_control_request_class(usbd_device *dev, struct usb_setup_data *req, uint8_t **buf, uint16_t *len,
		void (**complete)(usbd_device *dev, struct usb_setup_data *req))
{
	(void)complete;
	(void)dev;
	if((req->bRequest == USB_REQ_GET_REPORT) && USB_VAL_IS_FEATURE(req->wValue)) {
		//gpio_set(GPIOD, GPIO13);
		*buf = (uint8_t*) &params;
		*len = sizeof(struct params_t);
		return USBD_REQ_HANDLED;
	}
	if((req->bRequest == USB_REQ_SET_REPORT) && USB_VAL_IS_FEATURE(req->wValue)) {
		//gpio_set(GPIOD, GPIO13);
		memcpy(&params, *buf, sizeof(params));
		*buf = (uint8_t*) &params;
		*len = 0;

		return USBD_REQ_HANDLED;
	}
	return USBD_REQ_NOTSUPP;

}

