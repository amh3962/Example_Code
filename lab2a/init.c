#include "init.h"

void init_pa0( void )
{
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN ;		// enable clock for A group of GPIO
	GPIOA->MODER &= 0xABFFFFF0;							// clear out bits 0 to 3 for PA0 PA1
	GPIOA->MODER |= 0xABFFFFFA ;						// PA0 PA1 are now in input mode
  GPIOA->AFR[0] &= 0xFFFFFFF0;
  GPIOA->AFR[0] |= 0xFFFFFF11;
}
