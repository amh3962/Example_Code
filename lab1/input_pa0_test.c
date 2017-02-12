// L. Kiser Feb. 8, 2017

#include "stm32l476xx.h"
#include "input_pa0_test.h"
#include "LED.h"

// Turn on the peripheral clock for GPIOA
// and set PA0 to be input mode
void init_pa0( void )
{
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN ;		// enable clock for A group of GPIO
	GPIOA->MODER &= ~3 ;										// clear out bits 0 and 1 for PA0
																					// PA0 is now in input mode
	GPIOA->MODER |= 2 ;									// Enable alternate function mode (binary 10) for PA0
}

// Read the state of PA0 (high or low)
int read_pa0( void )
{
	return GPIOA->IDR & 1 ;				// read the bottom bit of the GPIOA input lines which is PA0.
																// returns 1 if high, 0 if low.
}

