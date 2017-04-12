#include <time.h>
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

timer_t PWM_A;
timer_t PWM_B;
struct sigevent PWM_A_Event;
struct sigevent PWM_B_Event;

void pin_init()
{
	ctrl_reg = mmap_device_io( PORT_LENGTH, CTRL_ADDRESS );
	out8( ctrl_handle, CTRL_init);
  
  portA = mmap_device_io( PORT_LENGTH, DIOA_Address); 
  portB = mmap_device_io( PORT_LENGTH, DIOB_Address);
}

void timer()
{
  timer_t             timerid;    // timer ID for timer
  struct sigevent     event;      // event to deliver
  struct itimerspec   timer;      // the timer data structure
  
  SIGEV_INTR_INIT(&event)
  
  timer_create (CLOCK_REALTIME, &event, &timerid)
  
  // setup the timer (20ms delay, 20ms reload)
    timer.it_value.tv_sec = 0;
    timer.it_value.tv_nsec = 20000000;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_nsec = 20000000;
    
  // Start Timer
    timer_settime (timerid, 0, &timer, NULL);
}

void * int_thread (void)
{
    // attach the ISR to IRQ 3
    InterruptAttach (0, isr_handler, NULL, 0, 0);

    // perhaps boost this thread's priority here

    // now service the hardware when the ISR says to
    while (1)
    {
        InterruptWait (NULL, NULL);
       
        //Set A0 and B0 output high
        out8(portA, 0x01);
        out8(portB, 0x01);
      
        PWM_timers();
    }
}

isr_handler (void, int id)
{
    // This causes the InterruptWait in "int_thread" to unblock.
    return (&event);
}



//ADD TO MAIN
  pthread_create (NULL, NULL, int_thread, NULL);
