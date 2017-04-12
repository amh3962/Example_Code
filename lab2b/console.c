#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void *input_check_runner(void *cmd) {
	char* command;
	command = (char*)cmd;
	printf("Input checker thread start\n");
	int cmd_i = 0;
	int c;
	int i = 0;

	while (i++<100) {
		printf("%d characters waiting\n", tcischars(STDIN_FILENO));
		sleep(1);
	}

	/*
	while(1) {
		c = getchar();
		printf( "\nYou entered: ");
		putchar(c);

		if (cmd_i == 2) {		// We have two characters in the command
			if (c == '\r') {	// The command has been entered
				printf("\n");
			}
		}
		else {
			if ((c>64 && c<91) || (c>96 && c<123)) {
				command[cmd_i] = c;
				command[cmd_i+1] = '\0';
				printf("%c",c);
				cmd_i++;
			}
		}
	}
	*/

	printf("Input checker thread exit\n");
	pthread_exit(NULL);
}
