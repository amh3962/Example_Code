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
	if (USART2->ISR & USART_ISR_RXNE) {	// Wait until RXNE (RX not empty) bit is set
		char c = (uint8_t)(USART2->RDR & 0xFF); // RXNE flag auto reset after reading DR
		if (cmd_count == 2) {
			// We already have two commands from the user
			// Wait for enter key, accept no more inputs
			if (c == '\r') {
				command[cmd_count]='\0';
				cmd_count = 0;	// Reset command count
				command[1] = '\0';
				// Print newline
				const char newLine[4] = " \r\n";
				USART_Write(USART2, (uint8_t *)newLine, strlen(newLine));
				return 1;
			}
		}
		// We are able to accept more input from the user
		else {
			command[cmd_count] = c;
			USART_Write(USART2, (uint8_t*)command+cmd_count, strlen(command+cmd_count));
			cmd_count++;
		}
	}
	return 0;
}

void printInt(int n) {
		uint8_t buffer[BufferSize];
    int s;
		s = sprintf((char *)buffer, "%d\r\n", n);
		USART_Write(USART2, buffer, s);
}
