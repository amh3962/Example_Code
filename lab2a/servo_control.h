#include "servo.h"

void initServos(void);
void restartRecipe(Servo*);
void moveCommand(Servo*, int);
void waitCommand(Servo*, int);
void pauseCommand(Servo*);
void continueCommand(Servo*);
void loopCommand(Servo*, int);
void endLoopCommand(Servo*);
void run(void);
void runInstruction(Servo*, unsigned char);
unsigned char getInstruction(Servo*);
int positionToPWMCount(int);
void moveServos(void);
