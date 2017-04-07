#include "customer.h"

#ifndef CUSTOMER_QUEUE_H_
#define CUSTOMER_QUEUE_H_

typedef struct Node {
	Customer* cust;
	struct Node* next;
} Node;

void enqueue(Customer*);
Customer* dequeue();
int isQueueEmpty();
void printQueue();
int getMaxDepth();

#endif /* CUSTOMER_QUEUE_H_ */
