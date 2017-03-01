#include "servo_control.h"
#include "console.h"
#include <string.h>
#include "timer.h"

#define MOV  				(0x20)
#define WAIT 				(0x40)
#define LOOP 				(0x80)
#define END_LOOP		(0xA0)
#define RECIPE_END	(0x00)
#define CMD_MASK		(0xE0)
#define VALUE_MASK	(0x1F)

// Given demo; end recipe then move; command error then move
unsigned char recipe0[] = { MOV+0,MOV+5,MOV+0,MOV+3,LOOP+0,MOV+1,MOV+4,END_LOOP,MOV+0,MOV+2,WAIT+0,MOV+3,WAIT+0,MOV+2,MOV+3,WAIT+31,WAIT+31,WAIT+31,MOV+4,RECIPE_END,MOV+0,0xFF,MOV+5,'\0' };
//unsigned char recipe0[] = { MOV+0,LOOP+31,MOV+1,END_LOOP,MOV+2,'\0' };
// Right to left; left to right; nested loop error then move
unsigned char recipe1[] = { MOV|0,MOV|1,MOV|2,MOV|3,MOV|4,MOV|5,MOV|4,MOV|3,MOV|2,MOV|1,MOV|0,LOOP+0,MOV|2,LOOP+2,MOV|3,END_LOOP,MOV|5,END_LOOP,MOV+2,'\0' };

Servo servo0 = {
	.recipe = recipe0,
	.position = -1,
	.i=0,
	.running=1,
	.loop=0,
	.loopstart=0,
	.loopcount=0,
	.waitcount=0
};

Servo servo1 = {
	.recipe = recipe1,
	.position = -1,
	.i=0,
	.running=1,
	.loop=0,
	.loopstart=0,
	.loopcount=0,
	.waitcount=0
};

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
	// move servo to position
	servo->position = pos;
	moveServos();
	// wait for servos to move
	waitCommand(servo,servo->position-pos);
}

/**
 * Moves both servos to their positions
 */
void moveServos() {
	// TODO: move servo to position
	int s0PWM = positionToPWMCount(servo0.position);
	int s1PWM = positionToPWMCount(servo1.position);
	setPulseWidth(s0PWM, s1PWM);
}

/**
 * Converts a servo position to PWM in count
 * .38ms - 2.1ms
 * 
 */
int positionToPWMCount(int pos) {
	return 30400 + (pos * 27520000);
}

/**
 * Idles a servo and decrements wait counter
 */
void waitCommand(Servo* servo, int times) {
	servo->waitcount = times+1;
	// put servo into a paused state, but don't accept continues
	// the count should be decremented by the timer
	pauseCommand(servo);
}

/**
 * Set the running flag off
 */
void pauseCommand(Servo* servo) {
	// set the servo running flag off
	servo->running = 0;
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
	}
	else {
		// The servo is paused
		// Check for the wait timer to signal continue
	}
	servo->i++;
}

unsigned char getInstruction(Servo* servo) {
	return servo->recipe[servo->i];
}
