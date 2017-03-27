#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <math.h>
#include <pthread.h>
#include <semaphore.h>
#include "customer_teller.h"

#define NUM_TELLERS 3
#define NUM_SECONDS_IN_DAY 25200
#define US_IN_SECOND 0


// Variables to aide in metric calculation
int total_customers_served = 0;
int total_customer_wait = 0;
int total_customer_teller = 0;
int total_teller_wait = 0;
int max_customer_wait = 0;
int max_depth_queue = 0;
int max_transaction_time = 0;


int main(int argc, char *argv[]) {
	// Create customers

	// Initialize simulation timer
	// 100 us / second

	// Start timer

	// Run the simulation
	// Run until all tellers are waiting and the end of day has been reached
	while(1) {
		// As customers arrive, check the semaphore to see if a teller is available
		// If a teller is available, send the customer to the teller
		// If all tellers are busy, send the customer to the queue
	}

	// Calculate and print metrics
	printMetrics();

	return EXIT_SUCCESS;
}


/*
 * Calculate and print the metrics after the simulation has run
 */
void printMetrics() {
	printf("Total customers served: %d\n", total_customers_served);
	printf("Average customer wait time: %d\n", total_customer_wait/total_customers_served);
	printf("Average customer time with teller: %d\n",0);
	// Per teller
	printf("Average teller time with customer: %d\n",0);
	printf("Maximum customer wait time: %d\n",0);
	printf("Maximum teller wait time: %d\n",0);
	printf("Maximum transaction time for tellers: %d\n", max_transaction_time);
	printf("Maximum depth of customer queue: %d\n", max_depth_queue);

}

char* secondsToString(int seconds) {
	int min = seconds / 60;
	int sec = seconds % 60;
	// Format to return
	return ("%d minutes, %d seconds",min,sec);
}
