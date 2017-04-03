#include "customer.h"

#ifndef CUSTOMER_QUEUE_H_
#define CUSTOMER_QUEUE_H_

typedef struct Node {
	Customer* cust;
	struct Node* next;
} Node;

void enqueue(Node*, Node*, Customer*);
Customer* dequeue(Node*, Node*);

#endif /* CUSTOMER_QUEUE_H_ */
