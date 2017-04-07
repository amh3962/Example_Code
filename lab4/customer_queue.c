#include<stdio.h>
#include<stdlib.h>
#include "customer_queue.h"

Node* front = NULL;
Node* back = NULL;

int max_depth = 0;
int current_depth = 0;

void enqueue(Customer* c) {
	Node* n = (Node*)malloc(sizeof(Node));
	n->cust = c;
	n->next = NULL;
	//printf("Enqueue new customer: %d, %d\n", n->cust->arrival_time, n->cust->transaction_time);
	if (front == NULL && back == NULL) {
		//printf("Put node as front\n");
		front = n;
		back = n;
	}
	else {
		//printf("Put node in back\n");
		back->next = n;
		back = n;
	}
	current_depth++;
	if (current_depth > max_depth) {
		max_depth = current_depth;
	}
}


Customer* dequeue() {
	Node* n = front;
	if (front == NULL) {
		return NULL;
	}
	Customer* c = front->cust;
	if (front == back) {
		front = NULL;
		back = NULL;
	}
	else {
		front = front->next;
	}
	free(n);
	current_depth--;
	return c;
}

int isQueueEmpty() {
	return front == NULL;
}

void printQueue() {
	if (front == NULL) {
		printf("Empty queue\n");
	}
	else {
		Node* curr = front;
		printf("Customers (transaction time): ");
		while(curr != NULL) {
			printf("%d ", curr->cust->transaction_time);
			curr = curr->next;
		}
		printf("\n");
	}
}


int getMaxDepth() {
	return max_depth;
}
