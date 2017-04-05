#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <sys/neutrino.h>
#include "timer.h"

static volatile sig_atomic_t called;
volatile int current_time = 0;

void timer_init() {
	//struct sigevent         event; //dont need?
	struct itimerspec itime;
	timer_t timer_id;

	if (timer_create(CLOCK_REALTIME, NULL, &timer_id)) {
		printf("Timer create failed");
		exit(0);
	}

	itime.it_value.tv_sec = 0;
	itime.it_value.tv_nsec = 100000;
	itime.it_interval.tv_sec = 0;
	itime.it_interval.tv_nsec = 100000; //100,000ns = 100us

	struct sigaction act;
	sigset_t set;

	sigemptyset( &set );
	sigaddset( &set, SIGUSR1 );

	act.sa_flags = 0;
	act.sa_mask = set;
	act.sa_handler = handler;
	sigaction( SIGUSR1, &act, NULL );

	timer_settime(timer_id, 0, &itime, NULL);
}


void handler( int signo ) {
    //Increment Time every 100us
	current_time++;
	//kill(getpid(), SIGUSR1);
}
