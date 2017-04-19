#ifndef TIMER_H_
#define TIMER_H_

void timer_init();
void * int_thread (void*);
void isr_handler (int);
void PWM_A_delay(int);
void PWM_B_delay(int);
void * PWM_A_Thread (void*);
void * PWM_B_Thread (void*);
const struct sigevent * timer_handler (void *, int);
const struct sigevent * PWM_A_handler (void *, int);
const struct sigevent * PWM_B_handler (void *, int);


#endif /* TIMER_H_ */
