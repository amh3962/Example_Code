#include "stm32l476xx.h"
#include "SysClock.h"
#include "timer.h"
#include "run.h"
#include "console.h"

#include <string.h>
#include <stdio.h>

char RxComByte = 0;
uint8_t buffer[BufferSize];
char str[] = "Give Red LED control input (Y = On, N = off):\r\n";
int status = 0;
int lower = 950;
char rxByte = 'Y';

int main(void){
	UART2_Init();
	// TODO: call init
	
	// POST
	status = post();
	// if post fail, prompt user for retry
	while (status == 0) {
		rxByte = postFailure();
		if (rxByte == 'Y' || rxByte == 'y'){
			status = post();
		}
		else if (rxByte == 'N' || rxByte == 'n'){
			break;
		}
	}
	
	// ask user for lower limit
	lower = getLimit(lower);
	// run continuously
	while (1) {
		run(lower);
		printHistogram(lower);
		rxByte = rerunPrompt();
		if (rxByte == 'N' || rxByte == 'n') {
			lower = getLimit(lower);
		}
	}
}
