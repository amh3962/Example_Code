// Servo states
enum servo_states
{
	state_position_0,
	state_position_1,
	state_position_2,
	state_position_3,
	state_position_4,
	state_position_5,
	state_unknown,
	state_moving,
	state_waiting,
	state_recipe_ended,
	state_error
};

// Events triggered by user
enum events
{
	recipe_pause,
	recipe_continue,
	user_entered_right,
	user_entered_left,
	noop,
	recipe_ended,
	recipe_restart
};
