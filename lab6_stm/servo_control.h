// Servo struct
typedef struct _Servo {
	int* position;	// current position
	int waitcount;	// counter for wait
} Servo;


// Initialization
void initServo(int*);

// Servo moving and waiting
void moveServo(int);
int positionToPWMCount(int);
void servoWait(void);
