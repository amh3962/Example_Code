#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include "timer2.h"
#include "servo.h"
#include "servo_control.h"
#include <sys/procmgr.h>
#include <sys/neutrino.h>
#include <termios.h>
#include <unistd.h>

int privity_err;

// Thread creation
pthread_t input_check_thread;
pthread_t timer1_thread;
pthread_t timer2_thread;
pthread_t wait1;
pthread_t wait2;
pthread_t run_thread;

// Command buffer
char command[3];
char buffer[65];


int main(int argc, char *argv[]) {
	//procmgr_ability(0,PROCMGR_AID_IO|PROCMGR_AID_INTERRUPT);
	privity_err = ThreadCtl( _NTO_TCTL_IO, NULL );
	if ( privity_err == -1 )
	{
		printf( "Can't get root permissions\n" );
		return -1;
	}
	// Welcome text
	printf("Lab2b - Yura Kim, Aaron Halling\n");

	pin_init();
	period_init();

	// Initialize timer threads
	// PWM timers
	pthread_create(&timer1_thread, NULL, servo1_thread, (void*) command);
	pthread_create(&timer2_thread, NULL, servo2_thread, (void*) command);
	// Wait timers
	pthread_create(&wait1, NULL, wait1_thread, (void*) command);
	pthread_create(&wait2, NULL, wait2_thread, (void*) command);

	// Run the program
	pthread_create(&run_thread, NULL, run, (void*) command);

	// Run the program
	while(1) {
		// Check for user input
		fgets(buffer, 64, stdin);
		command[0] = buffer[0];
		command[1] = buffer[1];
		command[2] = "\0";
	}

	return EXIT_SUCCESS;
}
