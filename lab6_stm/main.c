#include "SysClock.h"
#include "timer.h"
#include "init.h"
#include "servo_control.h"

#include <string.h>
#include <stdio.h>


int main(void){
	// Initialize
	System_Clock_Init();
	init_pa0();
	initTimer();
	
	int* position;
	
	// Init servos to starting position
	initServo(position);
	
	// Wait for a button press to start the servo
	
	
	// Run the servo
	while(1) {
		// Check for a new reading
		int i;
		if (i != *position) {
			moveServo(i);
		} else{
			servoWait();
		}
	}
}
