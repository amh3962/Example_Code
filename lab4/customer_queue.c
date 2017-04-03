#include<stdio.h>
#include<stdlib.h>
#include "customer_queue.h"


void enqueue(Node* front, Node* back, Customer* c) {
	Node* n = (Node*)malloc(sizeof(Node));
	n->cust = c;
	n->next = NULL;
	if (front == NULL && back == NULL) {
		front = back = n;
	}
	else {
		back->next = n;
		back = n;
	}
}


Customer* dequeue(Node* front, Node* back) {
	Node* n = front;
	if (front == NULL) {
		return NULL;
	}
	Customer* c = front->cust;
	if (front == back) {
		front = back = NULL;
	}
	else {
		front = front->next;
	}
	free(n);
	return c;
}
