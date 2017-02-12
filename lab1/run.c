// Code for post and run

// TIM2->CR2 enable & disable timer

/**
 * Performs Power On Self Test on GPIO port
 * 
 * @return 1 for success, 0 for failure
 */
int post(void) {
	// setup timer
	initTimer(0, 100000);
	// check for input
	// 1 for success, 0 for fail
	return 0;
}

/**
 * asdf
 */
void run(int lower) {
	// setup timer
	initTimer(1, lower);
	// setup data struc
	// take counts
}