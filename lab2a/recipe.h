#define MOV  				(0x20)
#define WAIT 				(0x40)
#define LOOP 				(0x80)
#define END_LOOP		(0xA0)
#define RECIPE_END	(0x00)
#define CMD_MASK		(0xE0)
#define VALUE_MASK	(0x1F)

// Given demo; end recipe then move; command error then move
unsigned char recipe1[] = { MOV+0,MOV+5,MOV+0,MOV+3,LOOP+0,MOV+1,MOV+4,END_LOOP,MOV+0,MOV+2,WAIT+0,MOV+3,WAIT+0,MOV+2,MOV+3,WAIT+31,WAIT+31,WAIT+31,MOV+4,RECIPE_END,MOV+0,0xFF,MOV+5,'\0' };
// Right to left; left to right; nested loop error then move
unsigned char recipe2[] = { MOV|0,MOV|1,MOV|2,MOV|3,MOV|4,MOV|5,MOV|4,MOV|3,MOV|2,MOV|1,MOV|0,LOOP+0,MOV|2,LOOP+2,MOV|3,END_LOOP,MOV|5,END_LOOP,MOV+2,'\0' };
	
unsigned char *recipes[] = { recipe1, recipe2 };

void restartRecipe(void);

void move(int pos);

void wait(int times, int start);

void loop(int times);

void runRecipe(void);
