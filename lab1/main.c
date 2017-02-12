#include "stm32l476xx.h"
#include "SysClock.h"
#include "timer.h"
#include "run.h"
#include "console.h"
#include "UART.h"

#include <string.h>
#include <stdio.h>

char RxComByte = 0;
uint8_t buffer[BufferSize];
int status = 0;
int lower = 950;
char rxByte;
char str[] = "\n\nLab 1 - Yura Kim, Aaron Halling\r\n\n";

int main(void){
    // Initialize
    System_Clock_Init();
	UART2_Init();
	
    // Intro text
    USART_Write(USART2, (uint8_t *)str, strlen(str));
	
    // POST
	status = post();
	while (status == 0) {   // if POST fails, prompt user to retry
		rxByte = postFailure();
		if (rxByte == 'Y' || rxByte == 'y'){
			status = post();
		}
		else if (rxByte == 'N' || rxByte == 'n'){
			break;
		}
	}
    
	// Run continuously
	while (1) {
        lower = getLimit(lower);    // display and confirm limits
		run(lower);                 // run
		printHistogram(lower);      // print histogram
	}
}
