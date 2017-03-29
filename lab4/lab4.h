#ifndef LAB4_H_
#define LAB4_H_

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <math.h>
#include <pthread.h>
#include <semaphore.h>
#include "customer_teller.h"
#include "customer_queue.h"

int main();
void printMetrics();
char* secondsToString(int seconds);

#endif /* LAB4_H_ */
