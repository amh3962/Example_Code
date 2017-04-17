#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "console.h"
#include "timer.h"
#include "servo.h"
#include "servo_control.h"
#include <unistd.h>


// Thread creation
pthread_t input_check_thread;
pthread_t timer_thread;

// Command buffer
char *command[3];


int main(int argc, char *argv[]) {
	// Welcome text
	printf("Lab2b - Yura Kim, Aaron Halling\n");

	// Initialize Servos
		// Set both servos to position 4
		// Wait for servos to move 3 positions

	// Initialize console thread
	pthread_create(&input_check_thread, NULL, input_check_runner, (void*) command);
	// Initialize timer threads
	pthread_create(&timer_thread, NULL, int_thread, NULL);

	run();

	FILE *fp;
	int c;

	int cmd_i = 0;
	fp = freopen(STDIN_FILENO , "r", stdin );
	while(1) {
		c = getchar();
		printf("getchar() = ");
		putchar(c);
		printf("\n");
		/*
		if (cmd_i == 2) {
			if (c == '\r' || c == '\n') {
				cmd_i = 0;
				printf(command);
				printf(" command\n");
			}
		} else {
			if ((c > 64 && c < 91) || (c > 96 && c < 123)) {
				putchar(c);
				command[cmd_i] = c;
				command[cmd_i+1] = '\0';
				cmd_i++;
			}
		}
		*/
	}
	/*
	while( ( c = getchar() ) != EOF ) {
		putchar(c);
	}
	*/

	fclose( fp );

	return EXIT_SUCCESS;

	return EXIT_SUCCESS;
}
