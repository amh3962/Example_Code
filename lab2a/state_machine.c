#include "state_machine.h"

static enum servo_states servo_state1 = -1;
static enum servo_states servo_state2 = -1;

void process_command( enum user_command one_event )
{
	((uint8_t)(USARTx->RDR & 0xFF)
	switch ( servo_state1 )
	{
		case -1 :		// Starting from unknown state
			break ;
		case 0 :		// Position 0
			if ( one_event == user_entered_left )
			{
				move( state_position_1 ) ;
				current_servo_state = state_moving ;		// when the move ends (enough time has elapsed) new state will be state_position_1
			}
			// define to keep modular
			process_postition(new_state);
		case 1 :
			break ;
		case 2 :
			break ;
		case 3 :
			break ;
		case 4 :
			break ;
		case 5 :
			if ( one_event == user_entered_right )
			{
				move( state_position_1 ) ;
				current_servo_state = state_moving ;		// when the move ends (enough time has elapsed) new state will be state_position_1
			}
			break ;
	}
}
