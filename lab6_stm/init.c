#include "init.h"

void init_pins( void )
{
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN ;		// enable clock for A group of GPIO
	GPIOA->MODER &= 0xABFFFFF0;							// clear out bits 16 to 19 for PA0 and PA1
	GPIOA->MODER |= 0xABFFFFFA ;						// PA8 and PA9 are now in Alt Function mode
  GPIOA->AFR[0] &= 0xFFFFFFF0;
  GPIOA->AFR[0] |= 0xFFFFFF11;            //Select Alt function 1 for PA9 and PA9
}
