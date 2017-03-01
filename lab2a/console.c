#include "console.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// Code for console and user interaction

int cmd_count = 0;		// Number of commands inputted by user; wait for two

/**
 * Checks for user input
 * Waits for two chars and enter key to return signal for command processing
 * 
 * @return 1 if ready to process user commands, 0 if not
 */
int checkInput(char *command) {
	if (USART2->ISR & USART_ISR_RXNE) {
		char c = (uint8_t)(USART2->RDR & 0xFF);
		// We already have two commands from the user
		// Wait for enter key, accept no more inputs
		if (cmd_count == 2) {
			if (c == '\r') {
				command[cmd_count]='\0';
				cmd_count = 0;	// Reset command count
				return 1;
			}
		}
		// We are able to accept more input from the user
		else {
			USART_Write(USART2, (uint8_t*)c, 1);
			command[cmd_count] = c;
			cmd_count++;
		}
	}
	return 0;
}
