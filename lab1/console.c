#include "console.h"

// Code for console and user interaction

char post_fail_str[] = "POST fail. Would you like to retry? (Y = yes, N = no)\r\n";
char prompt_limit_str[] = "Accept the limits? (Y = yes, N = no)\r\n";
char limit_error_str[] = "Lower limit must be in range (50,9950).\r\n";
char new_limit_str[] = "New lower limit (microseconds):\r\n";
char rerun_str[] = "Rerun with same limits? (Y = yes, N = no)\r\n";

/**
 * Prompts user for POST retry.
 * 
 * @return user's response to prompt
 */
char postFailure(void) {
    USART_Write(USART2, (uint8_t *)post_fail_str, strlen(post_fail_str));
    return USART_Read(USART2);
}

/**
 * Prints the lower and upper limits. Prompts user for acceptance of limits.
 * 
 * @return user response to prompt
 */
char printRange(int lower) {
    uint8_t buffer[BufferSize];
    int n = 0;
    n = sprintf((char *)buffer, "\nLower limit: %d microseconts\r\n", lower);
    n += sprintf((char *)buffer + n, "Upper limit: %d microseconds\r\n", lower+100);
	USART_Write(USART2, buffer, n);
	USART_Write(USART2, (uint8_t *)prompt_limit_str, strlen(prompt_limit_str));
	return USART_Read(USART2);
}

/**
 * Prompts the user for a new lower limit.
 * 
 * @return user response to prompt
 */
int newLowerLimit(void) {
	USART_Write(USART2, (uint8_t *)new_limit_str, strlen(new_limit_str));
	return USART_Read(USART2);
}

/**
 * Prints histogram. Prompts user to rerun with same limits.
 * 
 * @return user response to prompt
 */
char printHistogram(int lower) {
    char histogram_str[] = "Histogram results from limits (%d,%d):\r\n";
	USART_Write(USART2, (uint8_t *)histogram_str, strlen(histogram_str));
    USART_Write(USART2, (uint8_t *)rerun_str, strlen(rerun_str));
	return USART_Read(USART2);
}

/**
 * Prompts user for new limits.
 * 
 * @return new lower limit
 */
int getLimit(int lower) {
	char rxByte = 'N';

	rxByte = printRange(lower); // display current limits and prompt for change
	while (rxByte == 'n' || rxByte == 'n') {    // change limits
		lower = newLowerLimit();
			if (lower < 50 || lower > 9950) {   // limits check
				USART_Write(USART2, (uint8_t *)limit_error_str, strlen(limit_error_str));
				rxByte = 'N';
			}
			else {
				rxByte = printRange(lower);     // display new limits and prompt for change
			}
	}
    return 0;
}
