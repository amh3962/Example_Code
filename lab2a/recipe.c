#include "recipe.h"

// Index for recipe instruction to run
int i0 = 0;
int i1 = 0;

// Paused flags
int p0 = 0;
int p1 = 0;

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
	char cmd = 0;
	while ((recipes[0][i0] != '\0') || (recipes[1][i1] != '\0')) {
		// Check for user input
		// Set pause flags on/off
		// Servo 1
		if (p0 != 0) i0 = runInstruction(recipes[0],i0);
		// Servo 2
		if (p1 != 0) i1 = runInstruction(recipes[1],i1);
	}
}

void runInstruction(unsigned char recipe[], int i) {
	cmd = recipe[i];
	// Check for end of recipe instruction
	if (cmd == 0)
		// set servo to pause
		return i;									// don't move on in instructions
	// Parse command
	if (cmd & CMD_MASK == MOV)	// move
		move(cmd & VALUE_MASK)
	if (cmd & CMD_MASK == WAIT)	// wait
		wait(cmd & VALUE_MASK)
	if (cmd & CMD_MASK == LOOP)
		loop(cmd & VALUE_MASK, i)
	return i++;
}
