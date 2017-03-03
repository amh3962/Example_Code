#include "servo_control.h"
#include "console.h"
#include <string.h>
#include <stdlib.h>
#include "timer.h"
#include "led.h"

#define MOV  				(0x20)
#define WAIT 				(0x40)
#define LOOP 				(0x80)
#define END_LOOP		(0xA0)
#define RECIPE_END	(0x00)
#define CMD_MASK		(0xE0)
#define VALUE_MASK	(0x1F)

// Given demo; end recipe then move; command error then move
unsigned char recipe0[] = { MOV+0,MOV+5,MOV+0,MOV+3,LOOP+0,MOV+1,MOV+4,END_LOOP,MOV+0,MOV+2,WAIT+0,MOV+3,WAIT+0,MOV+2,MOV+3,WAIT+31,WAIT+31,WAIT+31,MOV+4,RECIPE_END,MOV+0,0xFF,MOV+5,'\0' };
//unsigned char recipe1[] = { MOV+0,WAIT+31,LOOP+31,MOV+5,MOV+0,END_LOOP,MOV+2,'\0' };
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
	.waittimer=1,
	.waitcount=0,
	.errorstate=0,
	.paused=0
};

Servo servo1 = {
	.recipe = recipe1,
	.position = -1,
	.i=0,
	.running=0,
	.loop=0,
	.loopstart=0,
	.loopcount=0,
	.waittimer=5,
	.waitcount=0,
	.errorstate=0,
	.paused=0
};

/**
 * Initializes the servos
 */
void initServos() {
	// move the servos to the starting position
	servo0.position = 4;
	servo1.position = 4;
	moveServos();
	// wait for servos to move
	waitCommand(&servo0,3);
	waitCommand(&servo1,3);
	greenLEDOn();
	redLEDOff();
}

/**
 * Restart the servo on its recipe
 */
void restartRecipe(Servo *servo) {
	servo->i = 0;
	servo->running = 1;
	servo->paused = 0;
}

/**
 * Moves a servo to a position
 */
void moveCommand(Servo* servo, int pos) {
	// wait for servo to move
	servo->position = pos;
	moveServos();
	waitCommand(servo,abs(servo->position-pos)*2);
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
 * Indicates a nested loop error
 */
void nestedLoopError(Servo* servo) {
	// update LED with state - green off, red on
	greenLEDOff();
	redLEDOn();
}

/**
 * Indicates a command error
 */
void commandError(Servo* servo) {
	// update LED with state - green on, red on
	greenLEDOn();
	redLEDOn();
}

/**
 * Set the running flag off
 * Called by waitCommand and user pause command
 */
void recipePause(Servo* servo) {
	// set the servo running flag off
	servo->running = 0;
  // start wait timer
	startTimer(servo->waittimer);
	// update LED with state - green off, red off
	greenLEDOff();
	redLEDOff();
}

/**
 * Set the running flag on
 * Called by end of wait and user continue command
 */
void recipeContinue(Servo* servo) {
	// set the servo running flag off
	servo->running = 1;
  // stop Wait Timer
	stopTimer(servo->waittimer);
	// update LED with state - green on, red off
	greenLEDOn();
	redLEDOff();
}

/**
 * Converts a servo position to PWM in count
 * 2% = .4ms = 4
 * 10% = 2ms = 20
 * 4, 7, 10, 13, 16, 19 - for relatively equal spacing
 * 
 */
int positionToPWMCount(int pos) {
	return (4 + (pos*3));
}

/**
 * Pauses a servo and sets the wait count
 */
void waitCommand(Servo* servo, int times) {
	servo->waitcount = times+1;
	// the count should be decremented by the timer
	recipePause(servo);
}

/**
 * Runs one recipe instruction for each servo motor
 */
void loopCommand(Servo* servo, int times) {
	if (servo->loop) {
		nestedLoopError(servo);
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
	//if (instruction != '\0') {			// While not end of recipe
	//	runInstruction(&servo0, instruction);
	//}
	instruction = getInstruction(&servo1);
	if (instruction != '\0') {			// While not end of recipe
		runInstruction(&servo1, instruction);
	}
}

/**
 * Runs one recipe instruction from the given recipe
 */
void runInstruction(Servo* servo, unsigned char instruction) {
	// DEBUG
	// print instruction index being run
	// printInt(servo->i);
	
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
			// RECIPE_END doesn't do anything
			// recipe end is indicated by a paused recipe without a waitcount
		}
		servo->i++;
	}
	else {
		// The servo is paused
		// Did the user pause the recipe
		if (servo->paused) return;
		// Check the wait timer for the servo
		// Decrement count as needed
		if (checkWait(servo->waittimer)) decrementWait(servo);
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
void decrementWait(Servo* servo) {
  servo->waitcount--;						// Decrement wait count
	if (servo->waitcount == 0) {	// If the wait is done
	  recipeContinue(servo);			// Run the servo
	}
}



					/////////////////////////////////////
					//          USER COMMANDS          //
					/////////////////////////////////////

/*
 * Validate and process user command
 *
 * return 1 if success, 0 if error(s)
 */
int processCommands(char* commands) {
	return processCommand(&servo0, commands[0]) && processCommand(&servo1, commands[1]);
}

/*
 * Process user command
 * 
 * return 1 if success, 0 if error
 */
int processCommand(Servo* servo, char command) {
	if (command == 'P' || command == 'p') {
		// Pause recipe
		// Does not work in error state or after recipe end
		if (!((servo->errorstate) || ((!servo->running) && (servo->waitcount==0)))) {
			// Set user pause flag
			servo->paused = 1;
			recipePause(servo);
		}
		return 1;
	}
	if (command == 'C' || command == 'c') {
		// Continue recipe
		// Does not work after recipe end or error state
		// User pause flag must be set
		if (!((servo->errorstate) || ((!servo->running) && (servo->waitcount==0)))) {
			if (servo->paused) recipeContinue(servo);
			servo->paused=0;
		}
		return 1;
	}
	if (command == 'R' || command == 'r') {
		// Move servo right
		// Does not work if recipe is running
		if (!(servo->running) || (servo->position == 0)) {
			servo->position = servo->position-1;
		}
		return 1;
	}
	if (command == 'L' || command == 'l') {
		// Move servo left
		// Does not work if recipe is running
		if (!(servo->running) || (servo->position == 5)) {
			servo->position = servo->position+1;
		}
		return 1;
	}
	if (command == 'N' || command == 'n') {
		// No-op
		return 1;
	}
	if (command == 'B' || command == 'b') {
		// Restart and run recipe
		restartRecipe(servo);
		return 1;
	}
	return 0;
}
