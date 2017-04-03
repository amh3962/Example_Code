#include "lab4.h"

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <math.h>
#include <pthread.h>
#include <semaphore.h>
#include "customer.h"
#include "teller.h"
#include "customer_queue.h"
#include "timer.c"

#define NUM_TELLERS 3
#define NUM_SECONDS_IN_DAY 25200
#define US_IN_SECOND 100
#define MAX_CUSTOMERS_IN_DAY 254


// Variables to aide in metric calculation
int total_customers_served = 0;
int total_customer_wait = 0;
int total_customer_teller = 0;
int total_teller_wait = 0;
int max_customer_wait = 0;
int max_depth_queue = 0;
int max_transaction_time = 0;


// Customer queue
Node* front = NULL;
Node* back = NULL;


// Teller threads
pthread_t teller1;
pthread_t teller2;
pthread_t teller3;


int main(int argc, char *argv[]) {
	// Generate customers
	Customer *cust_gen[MAX_CUSTOMERS_IN_DAY];
	total_customers_served = generateCustomers(cust_gen, NUM_SECONDS_IN_DAY);

	// Initialize simulation timer
	// 100 us / second
	int current_time = 0;

	// Start timer
	timer_init();
	// TODO: setup time counter to use in timer.c

	// Run the simulation
	// Run until all tellers are waiting and the end of day has been reached
	int cust_index = 0;
	while(1) {
		// Check if a transaction is done

		// Check for arrival of customer
		if (current_time < NUM_SECONDS_IN_DAY) {
			if (cust_gen[cust_index]->arrival_time == current_time) {
				// A new customer has arrived
				Customer* c = cust_gen[cust_index];
				// Add the customer to the queue
				enqueue(front,back,c);
				cust_index++;
			}
		}

		// If teller(s) are free, find them customers
	}

	// Calculate and print metrics
	printMetrics();

	return 1;
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

/*
char* secondsToString(int seconds) {
	int min = seconds / 60;
	int sec = seconds % 60;
	// Format to return
	return ("%d minutes, %d seconds",min,sec);
}
*/
