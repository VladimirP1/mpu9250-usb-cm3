#include <util.h>

#pragma GCC push_options
#pragma GCC optimize ("O3")
void delayUS_DWT(uint32_t us) {
	//cm_disable_interrupts();
	volatile uint32_t cycles = (SystemCoreClock/1000000L)*us;
	volatile uint32_t start = dwt_read_cycle_counter();
	do  {
	} while(dwt_read_cycle_counter() - start < cycles);
	//cm_enable_interrupts();
}
void delayMS_DWT(uint32_t ms){
	while(ms--) delayUS_DWT(1000);
}
#pragma GCC pop_options
