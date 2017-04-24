#include "SysClock.h"
#include "timer.h"
#include "init.h"
#include "servo_control.h"

#include <string.h>
#include <stdio.h>


char command[3];

int main(void){
	// Initialize
	System_Clock_Init();
	init_pa0();
	initTimer();

	// Init servos to starting position
	initServos();
	
	while(1) {
		if(checkInput(command)) {							// Check for user command
			// At this point command is a string of two alphabet characters
			int err = !processCommands(command);	// Process user commands
			if (err) {
				USART_Write(USART2, (uint8_t *)err_str, strlen(err_str));
			}
		}
		run();																// Run next instruction from recipes
	}
}
