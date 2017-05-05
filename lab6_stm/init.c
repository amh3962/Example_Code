#include "init.h"

void init_pins( void )
{
	// enable clock for A, B and E group of GPIO
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;		
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN;
	
	GPIOA->MODER &= 0xABFFF000;							// clear out bits for PA0, 1, 2, 3, and 5
	GPIOA->MODER |= 0xABFFF302 ;						// PA0 is now in Alt Function mode
	
	// PB2, 3, 6 and 7 to input
	GPIOB->MODER &= 0xABFF000F;		
	
	//Set PE8 as output
	GPIOE->MODER &= 0xABF0FFFF;							
	GPIOE->MODER |= 0xABF1FFFF;							
	
	//Select Alt function 1 for PA0
  GPIOA->AFR[0] &= 0xFFFFFFF0;
  GPIOA->AFR[0] |= 0x00000001;            
}
