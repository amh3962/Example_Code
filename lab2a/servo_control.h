#include "servo.h"

void restartRecipe(Servo*);
void moveCommand(Servo*, int);
void waitCommand(Servo*, int);
void pauseCommand(Servo*);
void loopCommand(Servo*, int);
void endLoopCommand(Servo*);
void run(void);
void runInstruction(Servo*, unsigned char);
unsigned char getInstruction(Servo*);
