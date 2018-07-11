struct{
	uint8_t buf[128];
	uint32_t wpoint, rpoint, len;
} simq;

uint8_t push(void* x) {
	if(simq.len >= 8) return 0;
	memcpy(simq.buf + simq.wpoint, x, 16);
	simq.wpoint = (simq.wpoint + 16) % 128;
	simq.len ++;
	return 1;
}
uint8_t pop(void* x) {
	if(simq.len == 0) return 0;
	memcpy(x, simq.buf + simq.rpoint, 16);
	simq.rpoint = (simq.rpoint + 16) % 128;
	simq.len --;
	return 1;
}