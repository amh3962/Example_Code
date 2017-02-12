#include "stm32l476xx.h"
#include "SysClock.h"
#include "UART.h"
#include "timer.h"
#include "run.h"

#include <string.h>
#include <stdio.h>

char RxComByte = 0;
uint8_t buffer[BufferSize];
char str[] = "Give Red LED control input (Y = On, N = off):\r\n";
int status = 0;
int lower = 950;
int upper = 1050;


int main(void){
	UART2_Init();
	// call init
	
	// call post
	status = post();
	// if post fail, prompt user for retry
	while (status == 0) {
		USART_Write(USART2, (uint8_t *)"POST fail. Would you like to retry?\r\n\r\n", 41);
		rxByte = USART_Read(USART2);
		if (rxByte == 'Y' || rxByte == 'y'){
			status = post()
		}
		else if (rxByte == 'N' || rxByte == 'n'){
			break;
		}
	}
	
	// display default lower and upper limits
	USART_Write(USART2, (uint8_t *)"POST fail. Would you like to retry?\r\n\r\n", 41);
	// min 50, max 9950 for lower bound; check it
	// accept or change limits
	// call run
	run(lower);
	// print histogram
}
