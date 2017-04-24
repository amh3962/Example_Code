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
void initServo(int* pos) {
	servo.position = pos;
	// Servo starts at position 0
	*servo.position = 0;
	moveServo(0);
}

/**
 * Moves servo to new position
 * Call when position has changed
 */
void moveServo(int pos) {
	// calculate wait time for servo to move
	int wait = abs(*servo.position-pos) * 2;
	// Update servo position
	*servo.position = pos;
	// Change the PWM
	int PWM = positionToPWMCount(*servo.position);
	setPulseWidth(PWM);
	// Set the wait count for until the servo has reached its position
	servo.waitcount = wait;
}

/**
 * Converts a servo position to PWM in count
 * 2% = .4ms = 4
 * 10% = 2ms = 20
 * 4, 7, 10, 13, 16, 19 - for relatively equal spacing
 * 
 */
int positionToPWMCount(int pos) {
	if (pos == 0) {
		return 50;
	}
	if (pos == 1) {
		return 80;
	}
	if (pos == 2) {
		return 110;
	}
	if (pos == 3) {
		return 140;
	}
	if (pos == 4) {
		return 170;
	}
	if (pos == 5) {
		return 200;
	}
	return 50;
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
}
