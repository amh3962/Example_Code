#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <math.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include "customer.h"
#include "teller.h"
#include "customer_queue.h"
#include "timer.h"

#define NUM_TELLERS 3
#define NUM_SECONDS_IN_DAY 25200
#define US_IN_SECOND 100
#define MAX_CUSTOMERS_IN_DAY 254

int current_time;

// Variables to aide in metric calculation
int total_customers_generated = 0;
int total_customers_served = 0;
int total_customer_wait = 0;
int total_customer_teller = 0;
int total_teller_wait = 0;
int max_customer_wait = 0;
int max_teller_wait = 0;
int max_transaction_time = 0;
int number_of_teller_waits = 0;

pthread_mutex_t ml = PTHREAD_MUTEX_INITIALIZER;

int threads_running = 4;
Customer *cust_gen[MAX_CUSTOMERS_IN_DAY];


// Teller threads
pthread_t teller1;
pthread_t teller2;
pthread_t teller3;
pthread_t customer_queue_manager;
pthread_t timer_thread;


/*
 * Calculate and print the metrics after the simulation has run
 */
void printMetrics() {
	printf("Total customers served: %d\n", total_customers_served);
	printf("Average customer wait time in queue: %d\n", total_customer_wait/total_customers_served);
	printf("Average customer time with teller: %d\n", total_customer_teller/total_customers_served);
	printf("Average teller wait time for customer: %d\n",total_teller_wait/number_of_teller_waits);
	printf("Maximum customer wait time in queue: %d\n",max_customer_wait);
	printf("Maximum teller wait time for customer: %d\n",max_teller_wait);
	printf("Maximum transaction time for tellers: %d\n", max_transaction_time);
	printf("Maximum depth of customer queue: %d\n", getMaxDepth());
}


/*
 * Teller thread
 */
void *teller_runner(void *id) {
	long tid;
	tid = (long)id;
	printf("Teller thread %ld started!\n", tid);
	int waitStart = 0;
	// While there are customers in line or it's not the end of the day
	while(current_time < NUM_SECONDS_IN_DAY || !isQueueEmpty()) {
		// Access the queue
		pthread_mutex_lock(&ml);
		if (isQueueEmpty()) {
			pthread_mutex_unlock(&ml);
			// If the queue is empty, set waitStart
			if (waitStart == 0) {
				waitStart = current_time;
			}
		}
		else {
			// Did the teller have to wait?
			if (waitStart != 0) {
				int teller_wait = current_time - waitStart;	// How long the teller waited
				total_teller_wait += teller_wait;	// Add to total teller wait time
				if (teller_wait > max_teller_wait) {
					max_teller_wait = teller_wait;	// New max teller wait time
				}
				number_of_teller_waits++;
			}
			// If the queue is not empty, take the first customer
			Customer* c = dequeue();
			pthread_mutex_unlock(&ml);
			total_customer_teller += c->transaction_time;
			//printf("Got a customer for teller thread %ld\n", tid);
			int customer_wait = current_time - c->arrival_time;	// How long the customer waited
			total_customer_wait += customer_wait;	// Add to total customer wait time
			if (customer_wait > max_customer_wait) {
				max_customer_wait = customer_wait;	// New max customer wait time
			}
			waitStart = 0;	// Reset the waitStart since we're done waiting
			int end_transaction = current_time + c->transaction_time;	// When the transaction will be over
			if (c->transaction_time > max_transaction_time) {
				max_transaction_time = c->transaction_time;
			}
			while (current_time <= end_transaction) {
				;
			}
			total_customers_served++;
			//printf("Teller thread %ld has finished a transaction\n", tid);
		}
	}
	printf("Teller thread exit\n");
	threads_running--;
	pthread_exit(NULL);
}


/*
 * Customer thread
 */
void *customer_queue_runner(void *id) {
	printf("Customer queue thread started!\n");
	int cust_index = 0;
	// While there are generated customers to arrive
	while(cust_index < total_customers_generated) {
		Customer* c = cust_gen[cust_index];
		//printf("Looking at customer %d - %d\n", c->arrival_time, current_time);
		if (current_time % 1000 == 1) {
			printf("Looking at customer %d - %d\n", c->arrival_time, current_time);
		}
		if (c->arrival_time <= current_time) {
			//printf("Customer has arrived at %d\n", current_time);
			// Next customer has arrived
			pthread_mutex_lock(&ml);
			enqueue(c);
			//printQueue();
			cust_index++;	// Move onto next customer to arrive
			pthread_mutex_unlock(&ml);
		}
	}
	printf("Customer Queue Thread exit\n");
	threads_running--;
	pthread_exit(NULL);
}


/*
 * Timer thread
 */
void *timer_thread_runner(void *id) {
	printf("Timer thread started!\n");
	int run = 1;
	while (run) {
		struct timespec ts;
		ts.tv_sec = 0;
		ts.tv_nsec = 100;
		nanosleep(&ts, NULL);
		current_time+= 10;
		if (current_time == NUM_SECONDS_IN_DAY) {
			printf("EOD\n");
		}
		if (current_time % 1000 == 0) {
			printf("Time: %d  Customers served: %d\n",current_time, total_customers_served);
		}
		if (threads_running == 0) {
			run = 0;
		}
	}
	printf("Timer Thread exit\n");
	pthread_exit(NULL);
}


int main(int argc, char *argv[]) {
	printf("Lab 4 - Yura Kim, Aaron Halling\n\n");
	current_time = 0;

	// Generate customers
	total_customers_generated = generateCustomers(cust_gen, NUM_SECONDS_IN_DAY);
	printf("Generated %d customers\n", total_customers_generated);

	// Initialize the mutex
	// pthread_mutex_init(&ml, NULL);

	// The start customer queue thread
	pthread_create(&customer_queue_manager, NULL, customer_queue_runner, NULL);

	// Initialize the tellers
	pthread_create(&teller1, NULL, teller_runner, (void *)1);
	pthread_create(&teller2, NULL, teller_runner, (void *)2);
	pthread_create(&teller3, NULL, teller_runner, (void *)3);

	// Start timer - 100 us / second
	pthread_create(&timer_thread, NULL, timer_thread_runner, NULL);

	// Wait for the simulation to finish
	while (threads_running) {
		;
	}

	// Destroy the mutex
	pthread_mutex_destroy(&ml);
	// Calculate and print metrics
	printMetrics();

	return 1;
}
