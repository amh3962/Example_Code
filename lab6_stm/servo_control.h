// Servo struct
typedef struct _Servo {
	int position;	// current position
	int waitcount;	// counter for wait
} Servo;


// Initialization
void initServo(void);

// Servo moving and waiting
void moveServo(int);
int positionToPWMCount(int);
void servoWait(void);
int waiting(void);
