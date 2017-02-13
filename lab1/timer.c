#include "timer.h"
#include "stm32l476xx.h"

// Hardware code for timer initialization and setup

void initTimer(int direction, int count) {
	// direction: 0 for down 1 for up
	// count: number in microseconds
	RCC->APB1ENR1 |= 0x00000001;  //Timer 2 Clock Enable
	TIM2->PSC = 0x0000;  		//Timer Prescaler = 0
	TIM2->ARR = count; 			//Set auto-load value. Used in POST
	TIM2->CCMR1 |= 0x0001;  //Input Capture mode
	TIM2->CCER |= 0x0001; 	//Turn off output enable
	TIM2->CR1 &= 0x0000; 		//Reset control register
	TIM2->CR1 |= direction; //Set count direction. 0 = upcount, 1 = downcount
	
	int i;
	for (i = 0; i < 4000000; i++)
		;
}

int runTimer() {
    int result = 0;
	TIM2->EGR |= 0x0001; 		//Create update event
	
	TIM2->CR1 |= 0x0001;	//Start or stop timer (bit 0)
	while(result == 0)
	{
		if((TIM2->SR) && 0x0002)	 // Check for capture interupt
			{
				result = (TIM2->CCR1);  //Read counter value
				TIM2->CR1 &= 0xFFF0;
				return result;
			}
		if((TIM2->SR) && 0x0001) // Check for end of count
		{
			TIM2->CR1 &= 0xFFF0;
			return result;
		}
	}
    return 0;
}
