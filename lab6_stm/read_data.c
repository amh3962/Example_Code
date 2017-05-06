#include "stm32l476xx.h"
#include "read_data.h"

int get_data() {
	int pos = 0;
	int portA, portB, portE;
	portA = GPIOA->IDR & 0x0E;
	portB = GPIOB->IDR & 0xCC;
	portE = GPIOE->IDR & 0x0800;
	
	//pos = (portA>>1)|(portE>>5)|((portB&0x0C)<<2)|(portB&0xC0);
	pos = (portA>>1)|(portE>>8)|((portB&0x0C)<<2)|(portB&0xC0);
	return pos;
}
