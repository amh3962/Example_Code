#include <time.h>
#include <sys/siginfo.h>
#include <sys/neutrino.h>

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
        
        //TODO:Turn on output
    }
}

isr_handler (void, int id)
{
    // This causes the InterruptWait in "int_thread" to unblock.
    return (&event);
}

//ADD TO MAIN
  pthread_create (NULL, NULL, int_thread, NULL);