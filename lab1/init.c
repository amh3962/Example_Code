#include "init.h"

void init_pa0( void )
{
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN ;		// enable clock for A group of GPIO
	GPIOA->MODER &= ~3 ;										// clear out bits 0 and 1 for PA0
																					// PA0 is now in input mode
	GPIOA->MODER |= 2 ;									// Enable alternate function mode (binary 10) for PA0
    GPIOA->AFR[0] &= 0xFFFFFFF0;
    GPIOA->AFR[0] |= 0xFFFFFFF1;
}
