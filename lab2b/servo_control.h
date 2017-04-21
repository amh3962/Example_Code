#include "servo.h"

// Command
extern char command[3];

// Initialization and recipe restart
void initServos(void);
void restartRecipe(Servo*);

// Recipe commands
void moveCommand(Servo*, int);
void waitCommand(Servo*, int);
void loopCommand(Servo*, int);
void endLoopCommand(Servo*);

// Runs the recipe
void *run(void*);
void runInstruction(Servo*, unsigned char);
unsigned char getInstruction(Servo*);

// Servo states
void nestedLoopError(Servo*);
void commandError(Servo*);
void recipePause(Servo*);
void recipeContinue(Servo*);

// Interacts with hardware level code
int positionToPWMCount(int);
void moveServos(void);
void decrementWait(Servo*);

// User commands
int processCommands(char*);
int processCommand(Servo*, char);
