#ifndef SERVO_H_
#define SERVO_H_

typedef struct _Servo {
  unsigned char* recipe;
	int position;	// current position
	int i;			// recipe index
	int running;	// 1 for running, 0 for paused or waiting
	int loop;		// 1 for in loop, 0 for not in loop
	int loopstart;	// index for loop start
	int loopcount;	// counter for loop
	int waittimer;	// the timer used for the wait command
	int waitcount;	// counter for wait
	int recipeend;	// the end of the recipe was reached
	int errorstate;	// error
	int paused;		// user pause
} Servo;

#endif /* SERVO_H_ */
