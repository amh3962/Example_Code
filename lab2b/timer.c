#include <time.h>
#include <pthread.h>
#include <sys/siginfo.h>
#include <stdint.h>       /* for uintptr_t */
#include <hw/inout.h>     /* for in*() and out*() functions */
#include <sys/neutrino.h> /* for ThreadCtl() */
#include <sys/syspage.h>  /* for for cycles_per_second */
#include <sys/mman.h>     /* for mmap_device_io() */

#define PORT_LENGTH 1
#define CTRL_ADDRESS 0x28B
#define DIOA_Address 0x288
#define DIOB_Address 0x289
#define CTRL_init 0x00 //DIO A & B as output

uintptr_t ctrl_reg;
uintptr_t portA;
uintptr_t portB;

pthread_t timer_A_thread;
pthread_t timer_B_thread;

timer_t             PWM_A; 
struct sigevent     PWM_A_Event;
struct itimerspec   timer_PWM_A;


 timer_t             PWM_B;
 struct sigevent     PWM_B_Event;
 struct itimerspec   timer_PWM_B;

void pin_init()
{
  ctrl_reg = mmap_device_io( PORT_LENGTH, CTRL_ADDRESS );
  out8( ctrl_reg, CTRL_init);
  
  portA = mmap_device_io( PORT_LENGTH, DIOA_Address); 
  portB = mmap_device_io( PORT_LENGTH, DIOB_Address);
}

void timer()
{
  timer_t             timer;    // timer ID for timer
  struct sigevent     event;    // event to deliver
  struct itimerspec   timer;    // the timer data structure
        
  SIGEV_INTR_INIT(&event);
  SIGEV_INTR_INIT(&PWM_A_event);
  SIGEV_INTR_INIT(&PWM_B_event);
  
  timer_create (CLOCK_REALTIME, &event, &timerid);
  timer_create (CLOCK_REALTIME, &PWM_A_event, &PWM_A);
  timer_Create (CLOCK_REALTIME, &PWM_B_event, &PWM_B);
  
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
    timer_PWM_A.it_value.tv_sec = 0;
    timer_PWM_A.it_value.tv_nsec = delay_B;
    timer_PWM_A.it_interval.tv_sec = 0;
    timer_PWM_A.it_interval.tv_nsec = 0;   
}

void * int_thread (void)
{
    // attach the ISR to IRQ 0
    ThreadCtl( _NTO_TCTL_IO, NULL );
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

void * PWM_A_Thread (void)
{
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

void * PWM_B_Thread (void)
{
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

event * timer_handler (void, int timer)
{
    // This causes the InterruptWait in "timer_thread" to unblock.
    return (&event);
}

PWM_A_Event * PWM_A_handler (void, int PWM_A)
{
    // This causes the InterruptWait in "PWM_A_thread" to unblock.
    return (&PWM_A_Event);
}

PWM_B_Event * PWM_B_handler (void, int PWM_B)
{
    // This causes the InterruptWait in "PWM_B_thread" to unblock.
    return (&PWM_B_Event);
}

