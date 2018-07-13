#include <init.h>
#include <util.h>
#include <spi.h>
#include <mpu9250.h>
#include <usb.h>

struct spiHandle_t spi_hnd = {.spi = SPI1, .cs_port = GPIOA, .cs_pin = GPIO4};

int main(void)
{
    clk_setup();
	led_setup();
	spi_setup();

	//delayUS_DWT(1000);

	usbd_device * usb = usb_init();
	comms_init(usb);
	mpu_start(&spi_hnd);

	while(1) {
		usbd_poll(usb);
	}

	return 0;
}
