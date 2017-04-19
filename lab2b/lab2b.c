#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "console.h"
#include "timer.h"
#include "servo.h"
#include "servo_control.h"
#include <unistd.h>
#include <sys/procmgr.h>
#include <sys/neutrino.h>

int privity_err;

// Thread creation
pthread_t input_check_thread;
pthread_t timer_thread;

// Command buffer
char *command[3];


int main(int argc, char *argv[]) {
	procmgr_ability(0,PROCMGR_AID_IO|PROCMGR_AID_INTERRUPT);
	privity_err = ThreadCtl( _NTO_TCTL_IO, NULL );
	if ( privity_err == -1 )
	{
		printf( "Can't get root permissions\n" );
		return -1;
	}
	// Welcome text
	printf("Lab2b - Yura Kim, Aaron Halling\n");

	//Initialize timer
	timer_init();

	// Initialize Servos
		// Set both servos to position 4
		// Wait for servos to move 3 positions

	// Initialize console thread
	pthread_create(&input_check_thread, NULL, input_check_runner, (void*) command);
	// Initialize timer threads
	pthread_create(&timer_thread, NULL, int_thread, NULL);

	/*int c;
	int cmd_i = 0;

	while( ( c = getchar() ) != EOF ) {
		if (cmd_i < 2) {
			putchar(c);
			printf("%d\n", cmd_i);
		}
		if (c == 0x0A) {
			printf("linefeed");
			cmd_i = 0;
			printf("%d\n", cmd_i);
		}
		cmd_i++;
	}

	run();*/

	return EXIT_SUCCESS;
}
