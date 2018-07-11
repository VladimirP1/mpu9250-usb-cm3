#include <comms.h>

usbd_device * usb;
struct params_t params;
uint8_t if_started = 0;

struct{
	uint8_t buf[64];
	uint32_t wpoint, rpoint, len;
} simq;

uint8_t push(void* x) {
	if(simq.len >= 4) return 0;
	memcpy(simq.buf + simq.wpoint, x, 16);
	simq.wpoint = (simq.wpoint + 16) % 64;
	simq.len ++;
	return 1;
}
uint8_t pop(void* x) {
	if(simq.len == 0) return 0;
	memcpy(x, simq.buf + simq.rpoint, 16);
	simq.rpoint = (simq.rpoint + 16) % 64;
	simq.len --;
	return 1;
}

void comms_init(usbd_device * usbd){
	usb = usbd;
	memset(&params, 0, sizeof(struct params_t));
	while(!if_started);
	usbd_ep_write_packet(usb, 0x81, simq.buf, 32);
}

void comms_new_sample(uint8_t* buf){
	if(!if_started) return;

	uint32_t time = dwt_read_cycle_counter();

	buf[12] = time >> 24;
	buf[13] = time >> 16;
	buf[14] = time >> 8;
	buf[15] = time;

	cm_disable_interrupts();
	push(buf);
	cm_enable_interrupts();


}
void tx_callback(usbd_device *usbd_dev, uint8_t ep){
	static uint8_t localbuf[32];
	gpio_toggle(GPIOD, GPIO13);
	memset(localbuf, 0, 32);
	pop(localbuf);
	pop(localbuf + 16);
	usbd_ep_write_packet(usb, 0x81, localbuf, 32);
}
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
