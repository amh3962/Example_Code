#include "SysClock.h"
#include "timer.h"
#include "run.h"
#include "console.h"
#include "UART.h"
#include "init.h"

#include <string.h>
#include <stdio.h>

int status;
int lower = 950;
char rxByte;
char str[] = "\n\nLab 2a - Yura Kim, Aaron Halling\r\n\n";
int results[100];

int main(void){
    // Initialize
    System_Clock_Init();
	  UART2_Init();
    init_pa0();
		initTimer();
		
		// Designate recipe per servo
	
		// Start in pause state
		// When we get a user command		a,b
		// processEvent(servo1_state,a)
		// processEvent(servo2_state,b)
}
