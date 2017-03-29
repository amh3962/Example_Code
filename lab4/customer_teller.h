#ifndef CUSTOMER_TELLER_H_
#define CUSTOMER_TELLER_H_

typedef struct _Customer {
	int arrival_time;
	int transaction_time;
} Customer;

typedef struct _Teller {
	int status;
} Teller;

#endif /* CUSTOMER_TELLER_H_ */
