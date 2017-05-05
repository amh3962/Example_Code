#include "stm32l476xx.h"
#include "read_data.h"

int get_data() {
	int pos = 0;
	int portA, portB;
	portA = GPIOA->IDR & 0x2E;
	portB = GPIOB->IDR & 0xCC;
	
	pos = (portA&0x0E>>1)|(portA&0x20>>2)|(portB&0x0C<<2)|(portB&0xC0);
	return pos;
}
