enum recipe_status
{
	running,
	paused,
	command_error,
	nested_loop_error
};

// Events triggered by user
enum user_commands
{
	recipe_pause,
	recipe_continue,
	user_entered_right,
	user_entered_left,
	noop,
	recipe_restart
};
