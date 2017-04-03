#include "customer.h"

#include <stdlib.h>


/*
 * Returns the number of customers to be served that day
 */
int generateCustomers(Customer *cust_gen[], int num_seconds_in_day) {
	int start_time = 0;
	int total_customers = 0;
	while (start_time <= num_seconds_in_day) {
		Customer* new_cust = malloc(sizeof(Customer));
		new_cust->arrival_time = start_time;
		new_cust->transaction_time = randRange(30,480);	// 30-480 seconds
		cust_gen[total_customers] = new_cust;
		// Update the total number of customers to be served
		total_customers++;
		// Update the arrival time of the next customer
		start_time = start_time + randRange(60,240);	// 60-240 seconds
	}
	return total_customers;
}


/*
 * Returns a random integer between the min and max
 */
int randRange(int min, int max)
{
    int diff = max-min;
    return (int) (((double)(diff+1)/RAND_MAX) * rand() + min);
}
