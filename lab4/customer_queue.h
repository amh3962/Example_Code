#include "customer_teller.h"

#ifndef CUSTOMER_QUEUE_H_
#define CUSTOMER_QUEUE_H_

typedef struct Node {
	Customer* cust;
	struct Node* next;
} Node;

void Enqueue(Node*, Node*, Customer* c);
Customer* Dequeue(Node*, Node*);

#endif /* CUSTOMER_QUEUE_H_ */
