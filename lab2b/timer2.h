#ifndef TIMER2_H_
#define TIMER2_H_

void pin_init();
void *servo1_thread(void*);
void *servo2_thread(void*);
void servo1_delay(int);
void servo2_delay(int);
void *wait1_thread(void*);
void *wait2_thread(void*);
void period_init();

extern int wait_time1;
extern int wait_time2;

#endif /* TIMER2_H_ */
