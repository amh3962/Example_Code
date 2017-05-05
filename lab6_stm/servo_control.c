#include "servo_control.h"
#include <string.h>
#include <stdlib.h>
#include "timer.h"


Servo servo = {
	.position = NULL,
	.waitcount = 0,
};


/**
 * Initializes the servos
 */
void initServo() {
	// Servo starts at position 0
	moveServo(63);
	servo.position = 0;
	//setPulseWidth(40);
}

/**
 * Moves servo to new position
 * Call when position has changed
 */
void moveServo(int val) {
	int pos = 0;
	// Set pos from 0 to 125
	if (val < 63) {
		pos = 0;
	}
	else if (val > 188) {
		pos = 125;
	}
	else {
		pos = val - 63;
	}
	
	// calculate wait time for servo to move
	int wait = abs(servo.position-pos);
	// Update servo position
	servo.position = pos;
	// Change the PWM
	int PWM = positionToPWMCount(pos);
	setPulseWidth(PWM);
	// Set the wait count for until the servo has reached its position
	servo.waitcount = 1;
	startTimer();
}

/**
 * Converts a servo positions 0-125 to PWM in count
 * 2% = .4ms = 40
 * 10% = 2ms = 200
 * 
 */
int positionToPWMCount(int pos) {
	return (pos * 1.28) + 40;
}

/**
 * Servo is idle
 */
void servoWait() {
	// If the servo is waiting, updates servo move wait counter
	if (servo.waitcount > 0) {
		// Check to see if 100ms have passed
		if (checkWait()) servo.waitcount--;
	}
	if (servo.waitcount == 0) {
		stopTimer();
	}
}

/**
 * Check if servo is moving
 */
int waiting() {
	if(servo.waitcount == 0)
	{
		return 0;
	}
	return 1;
}
