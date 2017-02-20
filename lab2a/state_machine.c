#include "state_machine.h"

static enum servo_states servo_state1 = state_unknown;
static enum servo_states servo_state2 = state_unknown;

void process_event( enum events one_event )
{
	switch ( servo_state1 )
	{
		case state_position_0 :		// right-most position
			if ( one_event == user_entered_left )
			{
				start_move( state_position_1 ) ;
				current_servo_state = state_moving ;		// when the move ends (enough time has elapsed) new state will be state_position_1
			}
			break ;
		case state_position_1 :
			// define to keep modular
			process_postition(new_state);
		case state_unknown :
			break ;
		case state_recipe_ended :
			break ;
	}
}
