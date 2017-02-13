#include "run.h"
#include "console.h"

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
	initTimer(1, 8000000);
	result = runTimer();
	// check for input
	// 1 for success, 0 for fail
 return result;
}

void run(int lower, int* results) {
    
	int i;
	int n = 0;
	// setup timer
	initTimer(0,0);
	for(i = 0; i < 1000; i++)
	{
		n = (runTimer() / 80) - lower;
		// n is not formatted correctly, possibly different size so it's effecting lower
		printInt(n);
		results[n] += 1;
	}
}
