typedef struct _Servo {
  unsigned char* recipe;
	int position;		// current position
	int i;					// recipe index
	int running;		// 1 for running, 0 for paused or waiting
	int loop;				// 1 for in loop, 0 for not in loop
	int loopstart;	// index for loop start
	int loopcount;	// counter for loop
	int waitcount;	// counter for wait
} Servo;
