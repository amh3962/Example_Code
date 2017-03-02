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
unsigned char recipe0[] = { MOV+0,LOOP+31,MOV+1,END_LOOP,MOV+2,'\0' };
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
	servo0.position = 2;
	servo1.position = 3;
	moveServos();
	// wait for servos to move
	waitCommand(&servo0,abs(6));
	waitCommand(&servo1,abs(6));
	// start the recipes on the servos
	continueCommand(&servo0);
	continueCommand(&servo1);
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
 * 2% = .4ms = 4
 * 10% = 2ms = 20
 * 4, 7, 10, 13, 16, 19 - for relatively equal spacing
 * 
 */
int positionToPWMCount(int pos) {
  if(pos == 0)
  {
    return 4;
  }
  
  if(pos == 1)
  {
    return 7;
  }
  
  if(pos == 2)
  {
    return 10;
  }
  
  if(pos == 3)
  {
    return 13;
  }
  
  if(pos == 4)
  {
    return 16;
  }
  
  if(pos == 5)
  {
    return 19;
  }
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
  //start wait timer
  TIM5->CR1 |= 0x0001;
}

/**
 * Set the running flag on
 * Called by end of wait and user continue command
 */
void continueCommand(Servo* servo) {
	// set the servo running flag off
	servo->running = 1;
  //Stop Wait Timer
  TIM5->CR1 &= 0xFFFE;
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
		}
		servo->i++;
	}
	else {
		// The servo is paused  
    //Chech for end of 100ms timer count
    
    //Use TIM5->SR &= 0x0001 to check timer 5 end of count
    //Use TIM2->SR &= 0x0001 to check timer 2 end of count
    //TODO: Assign a wait timer to each servo
    
		/*if (TIM5->SR &= 0x0001) {
      servo->waitcount--;
		   if (servo->waitcount == 0) {
		     continueCommand(servo);
		   }
		 }*/
	}
}

unsigned char getInstruction(Servo* servo) {
	return servo->recipe[servo->i];
}
