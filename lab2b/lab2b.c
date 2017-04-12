#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "console.h"
#include "timer.h"
#include "servo.h"
#include "servo_control.h"


// Thread creation
pthread_t input_check_thread;
pthread_t timer_thread;

// Command buffer
char *command[3];


int main(int argc, char *argv[]) {
	// Initialize Servos
		// Set both servos to position 4
		// Wait for servos to move 3 positions

	// Welcome text
	printf("Lab2b - Yura Kim, Aaron Halling\n");

	// Initialize console thread
	pthread_create(&input_check_thread, NULL, input_check_runner, (void*) command);
	// Initialize timer threads
	pthread_create(&timer_thread, NULL, int_thread, NULL);

	return EXIT_SUCCESS;
}
