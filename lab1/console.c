// Code for console and user interaction

/**
 * Prompts user for POST retry.
 * 
 * @return user's response to prompt
 */
char postFailure(void) {
	USART_Write(USART2, (uint8_t *)"POST fail. Would you like to retry? (Y = yes, N = no)\r\n");
	return USART_Read(USART2);
}

/**
 * Prints the lower and upper limits. Prompts user for acceptance of limits.
 * 
 * @return user response to prompt
 */
char printRange(int lower) {
	USART_Write(USART2, (uint8_t *)"Lower limit: %d microseconds\r\n", lower);
	USART_Write(USART2, (uint8_t *)"Upper limit: %d microseconds\r\n", lower+100);
	USART_Write(USART2, (uint8_t *)"Accept the limits? (Y = yes, N = no)\r\n");
	return USART_Read(USART2);
}

/**
 * Prints a warning.
 */
void printRangeWarning(void) {
	USART_Write(USART2, (uint8_t *)"Lower limit must be in range (50,9950).\r\n");
}

/**
 * Prompts the user for a new lower limit.
 * 
 * @return user response to prompt
 */
int newLowerLimit(void) {
	USART_Write(USART2, (uint8_t *)"New lower limit (ms):\r\n");
	return USART_Read(USART2);
}

/**
 * Prints histogram. Prompts user to rerun with same limits.
 * 
 * @return user response to prompt
 */
char printHistogram(int lower) {
	USART_Write(USART2, (uint8_t *)"Histogram results from limits (%d,%d):\r\n", lower, lower+100);
	USART_Write(USART2, (uint8_t *)"Rerun with same limits? (Y = yes, N = no)\r\n");
	return USART_Read(USART2);
}

/**
 * Prompts user for new limits.
 * 
 * @return new lower limit
 */
int getLimit(int lower) {
	char rxByte = 'Y';

	// display current lower and upper limits
	rxByte = printRange(lower);
	// get new lower limit from user
	while (rxByte == 'n' || rxByte == 'n') {
		lower = newLowerLimit();
			if (lower < 50 || lower > 9950) {
				printRangeWarning();
				rxByte = 'N'
			}
			else {
				rxByte = printRange(lower);
			}
	}
}