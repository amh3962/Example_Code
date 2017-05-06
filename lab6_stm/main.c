#include "SysClock.h"
#include "timer.h"
#include "led.h"
#include "init.h"
#include "servo_control.h"
#include "read_data.h"
#include "UART.h"

#include <string.h>
#include <stdio.h>

void printInt(int n) {
	int bufferSize = 30;
	uint8_t buffer[bufferSize];
  int s;
	s = sprintf((char *)buffer, "%d\r\n", n);
	USART_Write(USART2, buffer, s);
}

int main(void){
	// Initialize
	System_Clock_Init();
	init_pins();
	initTimer();
	UART2_Init();
	LED_Init();
	
	// Init servos to starting position
	initServo();
	
	// Run the servo
	while(1){
			if((GPIOA->IDR & 0x20) != 0)
			{
				int i = 0;
				while(1) {
					// If we are in the expected range, move the servo
					while (waiting()) {
						servoWait();
					}
					// Get value
					i = get_data();
					// Check if input is out of expected range
					if (i < 63 || i > 188) {
						greenLEDOn();
					} else {
						greenLEDOff();
					}
				moveServo(i);
			}
		}
	}
}
