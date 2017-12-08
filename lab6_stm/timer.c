#include "timer.h"
#include "stm32l476xx.h"

// Hardware code for timer initialization and setup

// count: number in milliseconds
void initTimer(void) {
	//Timer 2 & 5 clock enable
	RCC->APB1ENR1 |= 0x00000009;
  //Timer 1 clock enable
	RCC->APB2ENR |= 0x00000800;
  
	//Timer 2 Setup -- Control servos
	TIM2->PSC = 800;  			//Timer Prescaler = 800; 10 microseconds per count
	TIM2->EGR |= 0x0001; 			//Create update event
	TIM2->ARR = 2000; 			//Set auto-load value; 2000 for 20 milliseconds
	TIM2->CCER &= 0x0000;			//Turn off input enable
	TIM2->CCMR1 &= 0x0000;
	TIM2->CCMR1 |= 0x0068;  		//Input Capture pwm mode 1 for channel 1 
	TIM2->CCER |= 0x0001; 			//Turn on output enable for channel 1 
	TIM2->CR1 &= 0x0000; 			//Reset control register
	TIM2->CR1 |= 0x0080;			//Auto loading
	
  //Timer 1 setup -- Wait Timer: Servo1
	TIM1->PSC = 8000;  			//100us count
	TIM1->EGR |= 0x0001; 			//Create update event
	TIM1->ARR = 200; 			//Set auto-load value. 100 for 10 ms
	TIM1->CCER &= 0x00000000; 		//Turn off input enable
	TIM1->CCMR1 &= 0x0000; 			//Capture frozen. Using as Timing Base
	TIM1->CR1 &= 0x0000; 			//Reset control register
	TIM1->CR1 |= 0x0010;		  	//Set count direction. 0 = upcount, 1 = downcount
	TIM1->EGR |= 0x0001;
  
  //Enable timer
	TIM2->CR1 |= 0x0001;
}

// count is 200 for 20 milliseconds
// Pulse Width Range from 4 to 20 to move servos 
void setPulseWidth(int count) {
	// Channel 1
	TIM2->CCR1 &= 0x0000;		//Reset the pulse width
	TIM2->CCR1 |= count;		//Set pulse width
	// Update event
	TIM2->EGR |= 0x0001;
}

void runWaitTimer() {
  //int result = 0;
	TIM5->SR &= 0x00000000;
	TIM5->CR1 |= 0x0001; // Start timer
}

// Check the specified timer
int checkWait() {
	if((TIM1->SR) & 0x0001) // Check for end of count
	{
		TIM1->SR &= 0x00000000;
		return 1;
	}
	return 0;
}

// Turns off the specified timer
void stopTimer() {
	TIM1->CR1 &= 0xFFFE;
}

// Turns on the specified timer
void startTimer() {
	TIM1->SR &= 0x00000000;
	TIM1->CR1 |= 0x0001;
}
