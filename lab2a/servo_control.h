#include "servo.h"

// Initialization and recipe restart
void initServos(void);
void restartRecipe(Servo*);

// Recipe commands
void moveCommand(Servo*, int);
void waitCommand(Servo*, int);
void pauseCommand(Servo*);
void continueCommand(Servo*);
void loopCommand(Servo*, int);
void endLoopCommand(Servo*);

// Runs the recipe
void run(void);
void runInstruction(Servo*, unsigned char);
unsigned char getInstruction(Servo*);

// Interacts with hardware level code
int positionToPWMCount(int);
void moveServos(void);
void decrementWait(void);
