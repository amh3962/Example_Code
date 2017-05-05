#include "SysClock.h"
#include "timer.h"
#include "led.h"
#include "init.h"
#include "servo_control.h"
#include "read_data.h"

#include <string.h>
#include <stdio.h>


int main(void){
	// Initialize
	System_Clock_Init();
	init_pins();
	initTimer();
	LED_Init();
	
	// Wait for a button/joystick press to start the servo
	
	
	// Init servos to starting position
	initServo();
	
	while(1) {
		;
	}
	
	// Run the servo
	while(1) {
		// Get value
		int i = get_data();
		// Check if input is out of expected range
		if (i < 63 || i > 188) redLEDOn();
		// If we are in the expected range, move the servo
		else {
			moveServo(i);
			servoWait();
		}
	}
}
