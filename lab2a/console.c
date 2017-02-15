#include "console.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// Code for console and user interaction

char post_fail_str[] = "POST fail. Would you like to retry? (Y = yes, N = no)\r\n";
char prompt_limit_str[] = "Accept the limits? (Y = yes, N = no)\r\n";
char limit_error_str[] = "Lower limit must be in range (50,9950).\r\n";
char new_limit_str[] = "New lower limit (microseconds):\r\n";
char rerun_str[] = "Rerun with same limits? (Y = yes, N = no)\r\n";
char run_str[] = "Running\r\n";

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
    int n;
    n = sprintf((char *)buffer, "\nLower limit: %d us\r\n", lower);
		USART_Write(USART2, buffer, n);
    n = sprintf((char *)buffer, "Upper limit: %d us\r\n", lower+100);
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
	  char rxByte;
		char limit[7];
		const char newLine[4] = " \r\n";
		int i = 0;
	
	  USART_Write(USART2, (uint8_t *)new_limit_str, strlen(new_limit_str));
	  rxByte = USART_Read(USART2);
		while (rxByte != '\r' && i < 4) {
				limit[i] = rxByte;
				limit[i+1]='\0';
				USART_Write(USART2, (uint8_t *)limit+i, strlen(limit+i));
			  rxByte = USART_Read(USART2);
				i++;
		}
		
		USART_Write(USART2, (uint8_t *)newLine, strlen(newLine));
	  return atoi(limit);
}

/**
 * Prints histogram. Prompts user to rerun with same limits.
 * 
 * @return user response to prompt
 */
void printHistogram(int lower, int* results) {
		uint8_t buffer[BufferSize];
    int n;
		int i;
    n = sprintf((char *)buffer, "Histogram results from limits (%d,%d):\r\n", lower, lower+100);
		USART_Write(USART2, buffer, n);
		for (i = 0; i<102;i++) {
			if (results[i] != 0 ) {
				uint8_t buffer[BufferSize];
				int s;
				s = sprintf((char *)buffer, "%d\t%d\r\n", i+lower, results[i]);
				USART_Write(USART2, buffer, s);
			}
		}
}

void printInt(int n) {
		uint8_t buffer[BufferSize];
    int s;
		s = sprintf((char *)buffer, "%d\r\n", n);
		USART_Write(USART2, buffer, s);
}

/**
 * Prompts user for new limits.
 * 
 * @return new lower limit
 */
int getLimit(int lower) {
	  char rxByte;
		int temp = lower;
	  rxByte = printRange(lower); // display current limits and prompt for change
		lower = temp;
	  while (rxByte == 'N' || rxByte == 'n') {    // change limits
		  lower = newLowerLimit();
			if (lower < 50 || lower > 9950) {   // limits check
				  USART_Write(USART2, (uint8_t *)limit_error_str, strlen(limit_error_str));
			}
			else {
				  rxByte = printRange(lower);     // display new limits and prompt for change
			}
	  }
    return lower;
}