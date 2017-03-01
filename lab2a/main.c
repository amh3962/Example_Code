#include "SysClock.h"
#include "timer.h"
#include "UART.h"
#include "init.h"
#include "state_machine.h"
#include "recipe.h"
#include "console.h"

#include <string.h>
#include <stdio.h>

int status;
int lower = 950;
char rxByte;
char str[] = "\n\nLab 2a - Yura Kim, Aaron Halling\r\n\n";
int results[100];
char command[3];

int main(void){
    // Initialize
    System_Clock_Init();
	  UART2_Init();
    init_pa0();
		initTimer();
	
		// Intro text
    USART_Write(USART2, (uint8_t *)str, strlen(str));
	
		while(1) {
				if(checkInput(command)) {	// Check for UART input
//						process_command();			// process user commands
				}
				runInstruction();						// Run next instruction from recipes
		}
}
