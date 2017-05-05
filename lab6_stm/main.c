#include "SysClock.h"
#include "timer.h"
#include "led.h"
#include "init.h"
#include "servo_control.h"
#include "read_data.h"
#include "UART.h"

#include <string.h>
#include <stdio.h>


int main(void){
	// Initialize
	System_Clock_Init();
	init_pins();
	initTimer();
	LED_Init();
	
	// Wait for a button/joystick press to start the servo
	/*
	 * LOOK IN 
	 * C:\Users\yxk7831\Downloads\STM32L476G-Discovery-Examples\STM32L476G-Discovery-Examples\Examples\BSP\Src
	 * FOR A JOYSTICK DEMO
	 */
	
	// Init servos to starting position
	initServo();
	
	// Run the servo
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
				redLEDOn();
			} else {
				redLEDOff();
			}
			moveServo(i);
	}
}
