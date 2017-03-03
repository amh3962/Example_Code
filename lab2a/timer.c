#include "timer.h"
#include "stm32l476xx.h"

// Hardware code for timer initialization and setup

// count: number in milliseconds
void initTimer(void) {
	//Timer 2 & 5 clock enable
	RCC->APB1ENR1 |= 0x00000009;
	
	//Timer 2 Setup
	TIM2->PSC = 800;  		//Timer Prescaler = 800; 10 microseconds
	TIM2->EGR |= 0x0001; 		//Create update event
	TIM2->ARR = 2000; 		//Set auto-load value; 2000 for 20 milliseconds
	TIM2->CCER &= 0x0000;		//Turn off input enable
	TIM2->CCMR1 &= 0x0000;
	TIM2->CCMR1 |= 0x6868;  //Input Capture pwm mode 1 for channel 1 & 2
	TIM2->CCER |= 0x0011; 	//Turn on output enable for channel 1 & 2
	TIM2->CR1 &= 0x0000; 		//Reset control register
	TIM2->CR1 |= 0x0080;		//Auto loading
	
	//Timer 5 setup
	TIM5->PSC = 0x0000;  			//Timer Prescaler = 0
	TIM5->EGR |= 0x0001; 			//Create update event
	TIM5->ARR = 8000000; 			//Set auto-load value. 100ms count
	TIM5->CCER &= 0x00000000; //Turn off input enable
	TIM5->CCMR1 &= 0x0000; 		//Capture frozen. Using as Timing Base
	TIM5->CR1 &= 0x0000; 			//Reset control register
	TIM5->CR1 |= 0x0010;		  //Set count direction. 0 = upcount, 1 = downcount
	TIM5->EGR |= 0x0001;
	
	runWaitTimer();
}

// count is 2000 for 20 milliseconds
void setPulseWidth(int count1, int count2) {
	// Channel 1
	TIM2->CCR1 &= 0x0000;		//Reset the pulse width
	TIM2->CCR1 |= count1;		//Set pulse width
	// Channel 2
	TIM2->CCR2 &= 0x0000;		//Reset the pulse width
	TIM2->CCR2 |= count2;		//Set pulse width
	// Update event
	TIM2->EGR |= 0x0001;
	TIM2->CR1 |= 0x0001;		//Enable timer
}

void runWaitTimer() {
  //int result = 0;
	TIM5->SR &= 0x00000000;
	TIM5->CR1 |= 0x0001; // Start timer

	/*
	while(result == 0)
	{
		if((TIM5->SR) & 0x0001) // Check for end of count
		{
			TIM5->CR1 &= 0xFFFE;
			return;
		}
	}
	*/
}

int checkWait() {
	if((TIM5->SR) & 0x0001) // Check for end of count
	{
		TIM5->CR1 &= 0xFFFE;
		return 1;
	}
	return 0;
}
