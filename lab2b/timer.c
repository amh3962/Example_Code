#include <time.h>
#include <pthread.h>
#include <sys/siginfo.h>
#include <stdint.h>       /* for uintptr_t */
#include <hw/inout.h>     /* for in*() and out*() functions */
#include <sys/neutrino.h> /* for ThreadCtl() */
#include <sys/mman.h>     /* for mmap_device_io() */
#include "timer.h"
#include <stdlib.h>
#include <stdio.h>

#define PORT_LENGTH 1
#define CTRL_ADDRESS 0x28B
#define DIOA_Address 0x288
#define DIOB_Address 0x289
#define CTRL_init 0x00 //DIO A & B as output

//Timer
timer_t             timerid;    // timer ID for timer
struct sigevent     event;    // event to deliver
struct itimerspec   timer;    // the timer data structure
//PWM_A
timer_t             PWM_A;
struct sigevent     PWM_A_Event;
struct itimerspec   timer_PWM_A;
//PWM_B
timer_t             PWM_B;
struct sigevent     PWM_B_Event;
struct itimerspec   timer_PWM_B;

uintptr_t ctrl_reg;
uintptr_t portA;
uintptr_t portB;

pthread_t timer_A_thread;
pthread_t timer_B_thread;

void pin_init()
{
  ctrl_reg = mmap_device_io( PORT_LENGTH, CTRL_ADDRESS );
  out8( ctrl_reg, CTRL_init);
  
  portA = mmap_device_io( PORT_LENGTH, DIOA_Address); 
  portB = mmap_device_io( PORT_LENGTH, DIOB_Address);
}

void timer_init()
{
  SIGEV_INTR_INIT(&event);
  SIGEV_INTR_INIT(&PWM_A_Event);
  SIGEV_INTR_INIT(&PWM_B_Event);
  
  timer_create (CLOCK_REALTIME, &event, &timerid);
  timer_create (CLOCK_REALTIME, &PWM_A_Event, &PWM_A);
  timer_create (CLOCK_REALTIME, &PWM_B_Event, &PWM_B);
  
  // setup the timer (20ms delay, 20ms reload)
    timer.it_value.tv_sec = 0;
    timer.it_value.tv_nsec = 20000000;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_nsec = 20000000;
    
  PWM_A_delay(1000000);
  PWM_B_delay(1000000);
        
  // Start Timer
    timer_settime (timerid, 0, &timer, NULL);
}

void PWM_A_delay(int delay_A)
{
    // setup the timer (delay_A, no reload)
    timer_PWM_A.it_value.tv_sec = 0;
    timer_PWM_A.it_value.tv_nsec = delay_A;
    timer_PWM_A.it_interval.tv_sec = 0;
    timer_PWM_A.it_interval.tv_nsec = 0;
}

void PWM_B_delay(int delay_B)
{
    // setup the timer (delay_B, no reload)
    timer_PWM_B.it_value.tv_sec = 0;
    timer_PWM_B.it_value.tv_nsec = delay_B;
    timer_PWM_B.it_interval.tv_sec = 0;
    timer_PWM_B.it_interval.tv_nsec = 0;
}

void * int_thread (void*a)
{
	printf("int_thread thread start\n");
    // attach the ISR to IRQ 0
    InterruptAttach (0, timer_handler, NULL, 0, 0);
 
    pthread_create(&timer_A_thread, NULL, PWM_A_Thread, NULL);
    pthread_create(&timer_B_thread, NULL, PWM_B_Thread, NULL);

    // now service the hardware when the ISR says to
    while (1)
    {
        InterruptWait (NULL, NULL);
       
        //Set A0 and B0 output high
        out8(portA, 0x01);
        out8(portB, 0x01);
        
        timer_settime (PWM_A, 0, &timer_PWM_A, NULL);
        timer_settime (PWM_B, 0, &timer_PWM_B, NULL);
    }
}

void * PWM_A_Thread (void *cmd)
{
	printf("PWM_A thread start\n");
    // attach the ISR to IRQ 0
    InterruptAttach (0, PWM_A_handler, NULL, 0, 0);

    // now service the hardware when the ISR says to
    while (1)
    {
        InterruptWait (NULL, NULL);
       
        //Set A0 output Low
        out8(portA, 0x00);
    }
}

void * PWM_B_Thread (void *cmd)
{
	printf("PWM_B thread start\n");
    // attach the ISR to IRQ 0
    InterruptAttach (0, PWM_B_handler, NULL, 0, 0);

    // now service the hardware when the ISR says to
    while (1)
    {
        InterruptWait (NULL, NULL);
       
        //Set B0 output Low
        out8(portB, 0x00);
    }
}

const struct sigevent * timer_handler (void * A, int timer)
{
    // This causes the InterruptWait in "timer_thread" to unblock.
    return (&event);
}

const struct sigevent * PWM_A_handler (void * A, int PWM_A)
{
    // This causes the InterruptWait in "PWM_A_thread" to unblock.
    return (&PWM_A_Event);
}

const struct sigevent * PWM_B_handler (void * A, int PWM_B)
{
    // This causes the InterruptWait in "PWM_B_thread" to unblock.
    return (&PWM_B_Event);
}

