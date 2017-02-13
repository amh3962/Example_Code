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
char str[] = "\n\nLab 1 - Yura Kim, Aaron Halling\r\n\n";
int results[101];

int main(void){
    // Initialize
    System_Clock_Init();
	  UART2_Init();
    init_pa0();
	
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
				// initialize results
				for (int i=0;i<102;i++) {
						results[i] = 0;
				}
        lower = getLimit(lower);    // display and confirm limits
		    run(lower, results);                 // run
		    printHistogram(lower, results);      // print histogram
	  }
}
