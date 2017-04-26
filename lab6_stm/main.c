#include "SysClock.h"
#include "timer.h"
#include "led.h"
#include "init.h"
#include "servo_control.h"

#include <string.h>
#include <stdio.h>


int main(void){
	// Initialize
	System_Clock_Init();
	init_pins();
	initTimer();
	LED_Init();
	
	int* position;
	
	// Wait for a button/joystick press to start the servo
	
	
	// Init servos to starting position
	initServo(position);
	
	// Run the servo
	while(1) {
		// Check if communication link is up
		// if (not connected) redLEDOn();
		// Get value
		int i = 50;
		// Check if input is out of expected range
		// TODO: Update expected range of values
		if (i < 0 || i >100) redLEDOn();
		else {
			// Check if the position has changed
			if (i != *position) {
				moveServo(i);
			} else{
				servoWait();
			}
		}
	}
}
