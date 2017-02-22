#define MOV  				(0x20)
#define WAIT 				(0x40)
#define LOOP 				(0x80)
#define END_LOOP		(0xA0)
#define RECIPE_END	(0x00)
#define CMD_MASK		(0xE0)

// Verify the servo moves to all positions
unsigned char right_to_left[] = { MOV|0,MOV|1,MOV|2,MOV|3,MOV|4,MOV|5,RECIPE_END };
unsigned char left_to_right[] = { MOV|5,MOV|4,MOV|3,MOV|2,MOV|1,MOV|0,RECIPE_END };
// End normally then MOV
unsigned char end_then_move[] = { MOV|0,MOV|1,RECIPE_END,MOV|5 };
// Error states
unsigned char recipe_command_error[] = { MOV|0,MOV|3,MOV|0,MOV|2,0xFF,MOV|5,RECIPE_END };
unsigned char nested_loop_error[] = { MOV|0,MOV|3,MOV|0,LOOP+0,MOV|2,LOOP+2,MOV|3,END_LOOP,MOV|5,END_LOOP,MOV|2,RECIPE_END };
// Demo
unsigned char given_demo[] = { MOV+0,MOV+5,MOV+0,MOV+3,LOOP+0,MOV+1,MOV+4,END_LOOP,MOV+0,MOV+2,WAIT+0,MOV+3,WAIT+0,MOV+2,MOV+3,WAIT+31,WAIT+31,WAIT+31,MOV+4 };

unsigned char *recipes[] = { recipe1, recipe2, NULL };