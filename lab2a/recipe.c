#include "recipe.h"

// Index for recipe instruction to run
int i0 = 0;
int i1 = 0;

// Integer for status of recipe/motor
// bit 0	: 0 if running, 1 if paused
// bit 1	: 0 if running, 1 if paused
// bit 2	: 0 if not in loop, 1 if in loop
// bit 3-8:	wait count; 0 if non left
int s0 = 0;
int s1 = 0;

void restartRecipe() {
	i0 = 0;
	i1 = 0;
}

void move(int pos) {
}

void wait(int times) {
}

void loop(int times, int start) {
}

// Keep running until both recipes reach an error state or end of recipe
void runRecipe() {
	while ((recipes[0][i0] != '\0') || (recipes[1][i1] != '\0')) {
		// Check for user input
		checkInput();
		// Set pause flags on/off
		// Servo 0
		if (s0 != 0) i0 = runInstruction(recipes[0],i0);
		// Servo 1
		if (s1 != 0) i1 = runInstruction(recipes[1],i1);
	}
}

void runInstruction(unsigned char recipe[], int i) {
	char cmd = recipe[i] & CMD_MASK;	// Mask and get the opcode
	// Check for end of recipe instruction
	switch(cmd) {
		case 0:
			// set servo to pause
			break;
		case MOV:
			move(cmd & VALUE_MASK);
		case WAIT:
			wait(cmd & VALUE_MASK);
		case LOOP:
			loop(5,i);
	}
	i++;
}
