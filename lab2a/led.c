#include "led.h"

void LED_Init(void){
	
	// Enable the peripheral clock of GPIO Port	
	RCC->AHB2ENR |= 0x00000012;
	
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

void redLEDOn(void){
	GPIOB->ODR |= 0x00000004; //on
}

void redLEDOff(void) {
	GPIOB->ODR &= 0xFFFFFFFB; //off
}

void greenLEDOn(void) {
	GPIOE->ODR |= 0x00000100; //on
}

void greenLEDOff(void) {
	GPIOE->ODR &= 0xFFFFFEFF; //off
}
