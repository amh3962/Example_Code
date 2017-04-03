#ifndef CUSTOMER_TELLER_H_
#define CUSTOMER_TELLER_H_

typedef struct _Customer {
	int arrival_time;
	int transaction_time;
} Customer;

int generateCustomers(Customer *[], int);
int randRange(int, int);

#endif /* CUSTOMER_TELLER_H_ */
