#include "run.h"

// Code for post and run

// TIM2->CR2 enable & disable timer

/**
 * Performs Power On Self Test on GPIO port
 * 
 * @return 1 for success, 0 for failure
 */
int post(void) {
	int result = 0;
	// setup timer
	result = initTimer(1, 8000000);
	// check for input
	// 1 for success, 0 for fail
 return result;
}

void run(int lower) {
    /*
	int result = 0;
	int i = 0;
	// setup timer
	for(i, i < 1000, i++)
	{
		result = initTimer(0, 0);
		array[i] = (result ;
		
	}
	// setup data struc
	// take counts
    */
}
