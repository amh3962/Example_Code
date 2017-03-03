#include "SysClock.h"
#include "timer.h"
#include "UART.h"
#include "init.h"
#include "servo_control.h"
#include "console.h"
#include "led.h"

#include <string.h>
#include <stdio.h>

char str[] = "\n\nLab 2a - Yura Kim, Aaron Halling\r\n\n";
char err_str[] = "User command error(s).\r\n";
char command[3];

int main(void){
	// Initialize
	System_Clock_Init();
	UART2_Init();
	init_pa0();
  LED_Init();
	initTimer();

	// Intro text
	USART_Write(USART2, (uint8_t *)str, strlen(str));

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
