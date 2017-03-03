#include "servo_control.h"
#include "console.h"
#include <string.h>
#include <stdlib.h>
#include "timer.h"

#define MOV  				(0x20)
#define WAIT 				(0x40)
#define LOOP 				(0x80)
#define END_LOOP		(0xA0)
#define RECIPE_END	(0x00)
#define CMD_MASK		(0xE0)
#define VALUE_MASK	(0x1F)

// Given demo; end recipe then move; command error then move
//unsigned char recipe0[] = { MOV+0,MOV+5,MOV+0,MOV+3,LOOP+0,MOV+1,MOV+4,END_LOOP,MOV+0,MOV+2,WAIT+0,MOV+3,WAIT+0,MOV+2,MOV+3,WAIT+31,WAIT+31,WAIT+31,MOV+4,RECIPE_END,MOV+0,0xFF,MOV+5,'\0' };
unsigned char recipe0[] = { MOV+0,LOOP+31,MOV+1,MOV+5,END_LOOP,MOV+2,'\0' };
// Right to left; left to right; nested loop error then move
unsigned char recipe1[] = { MOV|0,MOV|1,MOV|2,MOV|3,MOV|4,MOV|5,MOV|4,MOV|3,MOV|2,MOV|1,MOV|0,LOOP+0,MOV|2,LOOP+2,MOV|3,END_LOOP,MOV|5,END_LOOP,MOV+2,'\0' };

Servo servo0 = {
	.recipe = recipe0,
	.position = -1,
	.i=0,
	.running=0,
	.loop=0,
	.loopstart=0,
	.loopcount=0,
	.waitcount=0
};

Servo servo1 = {
	.recipe = recipe1,
	.position = -1,
	.i=0,
	.running=0,
	.loop=0,
	.loopstart=0,
	.loopcount=0,
	.waitcount=0
};

/**
 * Initializes the servos
 */
void initServos() {
	// move the servos to the starting position
	servo0.position = 0;
	servo1.position = 0;
	moveServos();
	// wait for servos to move
	waitCommand(&servo0,abs(5));
	waitCommand(&servo1,abs(5));
}

/**
 * Restart the servo on its recipe
 */
void restartRecipe(Servo *servo) {
	servo->i = 0;
}

/**
 * Moves a servo to a position
 */
void moveCommand(Servo* servo, int pos) {
	servo->position = pos;
	moveServos();
	// wait for servo to move
	waitCommand(servo,abs(servo->position-pos));
}

/**
 * Moves both servos to their positions
 */
void moveServos() {
	int s0PWM = positionToPWMCount(servo0.position);
	int s1PWM = positionToPWMCount(servo1.position);
	setPulseWidth(s0PWM, s1PWM);
}

/**
 * Converts a servo position to PWM in count
 * 2% = .38ms = 38
 * 10% = 2.1ms = 210
 * 38, 72, 106, 140, 174, 208
 * 
 */
int positionToPWMCount(int pos) {
	return 38 + (pos * 34);
}

/**
 * Pauses a servo and sets the wait count
 */
void waitCommand(Servo* servo, int times) {
	servo->waitcount = times+1;
	// put servo into a paused state, but don't accept continues
	// the count should be decremented by the timer
	pauseCommand(servo);
}

/**
 * Set the running flag off
 * Called by waitCommand and user pause command
 */
void pauseCommand(Servo* servo) {
	// set the servo running flag off
	servo->running = 0;
}

/**
 * Set the running flag on
 * Called by end of wait and user continue command
 */
void continueCommand(Servo* servo) {
	// set the servo running flag off
	servo->running = 1;
}

/**
 * Runs one recipe instruction for each servo motor
 */
void loopCommand(Servo* servo, int times) {
	if (servo->loop) {
		// TODO: nested loop error
	} else {
		servo->loop = 1;
		servo->loopstart = servo->i;
		servo->loopcount = times;
	}
}

/**
 * Reached the end of a loop
 */
void endLoopCommand(Servo* servo) {
	if (servo->loopcount > 0) {
		servo->i = servo->loopstart;
		servo->loop = 0;
		servo->loopcount--;
	}
}

/**
 * Runs one recipe instruction for each servo motor
 */
void run() {
	unsigned char instruction = getInstruction(&servo0);
	if (instruction != '\0') {			// While not end of recipe
		runInstruction(&servo0, instruction);
	}
	//instruction = getInstruction(&servo1);
	//if (instruction != '\0') {			// While not end of recipe
	//	runInstruction(&servo1, instruction);
	//}
}

/**
 * Runs one recipe instruction from the given recipe
 */
void runInstruction(Servo* servo, unsigned char instruction) {
	// DEBUG
	// print instruction index being run
	printInt(servo->i);
	
	if (servo->running) {
		// The servo is running
		switch(instruction & CMD_MASK) {
			case 0:
				// This is an error opcode
				break;
			case MOV:
				moveCommand(servo, instruction & VALUE_MASK);
				break;
			case WAIT:
				waitCommand(servo, instruction & VALUE_MASK);
				break;
			case LOOP:
				loopCommand(servo, instruction & VALUE_MASK);
				break;
			case END_LOOP:
				endLoopCommand(servo);
				break;
		}
		servo->i++;
	}
	else {
		// The servo is paused
		// Check timer5 for 100ms
		if (checkWait()) decrementWait();
		// Check the wait status for both servos
		// If we only check this one and the other servo has a wait timer that stops at the same time, we'll be 1 wait count late for the other
	}
}

/**
 * Get the next instruction for the serv
 */
unsigned char getInstruction(Servo* servo) {
	return servo->recipe[servo->i];
}

/**
 * Checks servos for wait status
 */
void decrementWait() {
	if (!servo0.running) {						// Servo 0 is paused
    servo0.waitcount--;							// Decrement wait count
		  if (servo0.waitcount == 0) {	// If the wait is done
		    continueCommand(&servo0);			// Run the servo
		}
	}
	if (!servo1.running) {						// Servo 1 is paused
		servo1.waitcount--;							// Decrement wait count
		  if (servo1.waitcount == 0) {	// If the wait is done
		    continueCommand(&servo1);		// Run the servo
		}
	}
}
