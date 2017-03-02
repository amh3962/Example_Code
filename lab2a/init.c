#include "init.h"

void init_pa0( void )
{
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN ;		// enable clock for A group of GPIO
	GPIOA->MODER &= 0xABF0FFFF;							// clear out bits 16 to 19 for PA8 and PA9
	GPIOA->MODER |= 0xABFAFFFF ;						// PA8 and PA9 are now in Alt Function mode
  GPIOA->AFR[1] &= 0xFFFFFF00;
  GPIOA->AFR[1] |= 0xFFFFFF11;            //Select Alt function 1 for PA9 and PA9
}

void LED_Init(void){
	
	// Enable the peripheral clock of GPIO Port	
	RCC->AHB2ENR |= 0x00000012
	
	// LD4 Red = PB2
	GPIOB->MODER &= 0xFFFFFFCF;  
	GPIOB->MODER |= 0x0000010;      //  Output(01)
	GPIOB->OSPEEDR &= 0xFFFFFFCF;
	GPIOB->OSPEEDR |= 0x00000030;  // High speed (11)
	GPIOB->OTYPER &= 0xFFFFFFBF;       // Push-pull
	GPIOB->PUPDR &= 0xFFFFFFCF;  // No pull-up, no pull-down
	
	// LD5 Green = PE8
	GPIOE->MODER &= 0xFFFCFFFF;  
	GPIOE->MODER |= 0x00010000;      //  Output(01)
	GPIOE->OSPEEDR &= 0xFFFCFFFF;
	GPIOE->OSPEEDR |= 0x00030000;  // High speed
	GPIOE->OTYPER &= 0xFFFBFFFF;       // Push-pull
	GPIOE->PUPDR   &= 0xFFFCFFFF;  // No pull-up, no pull-down
}
/*
  Red LED
  GPIOB->ODR |= 0x00000004; -on
  GPIOB->ODR &= 0xFFFFFFFB; -off
  
  Green LED
  GPIOE->ODR |= 0x00000100; -on
  GPIOE->ODR &= 0xFFFFFEFF; -off
*/
