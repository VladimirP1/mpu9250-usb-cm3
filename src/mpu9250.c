#include "mpu9250.h"
uint8_t buf[32];
struct spiHandle_t *g_spi;

void mpu_init(struct spiHandle_t* spi);
void mpu_reset_fifo(struct spiHandle_t* spi);
uint16_t mpu_count(struct spiHandle_t* spi);
void mpu_sendusb(uint8_t* data);

void mpu_start(struct spiHandle_t *spi) {
	g_spi = spi;
    delayUS_DWT(1000);
    spi_read_reg(spi, 0x75);
    spi_delay();
    spi_read_reg(spi, 0x75);
    spi_delay();
    spi_read_reg(spi, 0x75);
    spi_delay();
    mpu_init(spi);
	exti_setup();
}
void mpu_sendusb(uint8_t* data){
	comms_new_sample(&buf[0]);
	(buf[0]&0x80) ? gpio_set(GPIOD, GPIO12) : gpio_clear(GPIOD, GPIO12);
	(buf[2]&0x80) ? gpio_set(GPIOD, GPIO15) : gpio_clear(GPIOD, GPIO15);
}

void mpu_init(struct spiHandle_t* spi){
    spi_write_reg_d(spi, 0x6B, 0x80); // Reset all
    delayUS_DWT(5000);
    spi_write_reg_d(spi, 0x6B, 1); // Power up
    spi_write_reg_d(spi, 0x6c, 0); // Enable all sensors, all axes
    spi_write_reg_d(spi, 0x19, 0); //
    spi_write_reg_d(spi, 0x1a, 0x01); // DLPF
    spi_write_reg_d(spi, 0x1d, 0x01); // -||-
    spi_write_reg_d(spi, 0x23, 0x78); // FIFO setup
    spi_write_reg_d(spi, 0x37, 0x30); // int setup
    spi_write_reg_d(spi, 0x38, 0x01); // Data interrupt
    mpu_reset_fifo(spi);
}

void mpu_reset_fifo(struct spiHandle_t* spi) {
    spi_modeSlow(spi);
    spi_delay(10);
    uint8_t user_ctrl = spi_read_reg_d(spi, 0x6a) & (~0x44);
    uint8_t fifo_en = spi_read_reg_d(spi, 0x23);
    spi_write_reg_d(spi, 0x23, 0);
    spi_write_reg_d(spi, 0x6a, user_ctrl);
    spi_write_reg_d(spi, 0x6a, user_ctrl | 0x04);
    spi_write_reg_d(spi, 0x6a, user_ctrl | 0x40);
    spi_write_reg_d(spi, 0x23, fifo_en);
    spi_modeFast(spi);
    delayUS_DWT(50);

}

void mpu_getsample(){
	uint32_t time = dwt_read_cycle_counter();
	spi_delay();
	uint8_t n = mpu_count(g_spi)/12;
	for(int i = 0 ; i < n; i++) {
		spi_delay();
		spi_read_reg_burst(g_spi, 0x74, 12, buf);
		BUF_SET_TIME(buf, time);
		mpu_sendusb(buf);
		spi_delay();
	}
	delayUS_DWT(4);
	if(n > 39){
		//gpio_set(GPIOD, GPIO13);
		//delayMS_DWT(1000);
		//gpio_clear(GPIOD, GPIO13);
		mpu_reset_fifo(g_spi);
	}
}

uint16_t mpu_count(struct spiHandle_t* spi) {
    return spi_read_reg16(spi, 0x72);
}





