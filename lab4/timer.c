//struct sigevent         event; //dont need?
struct itimerspec       itime;
timer_t                 timer_id;

   timer_create(CLOCK_REALTIME, NULL, &timer_id);

   itime.it_value.tv_sec = 0;
   itime.it_value.tv_nsec = 100000; 
   itime.it_interval.tv_sec = 0;
   itime.it_interval.tv_nsec = 100000; //100,000ns = 100us
   timer_settime(timer_id, 0, &itime, NULL);

extern void handler();
struct sigaction act;
sigset_t set;

sigemptyset( &set );
sigaddset( &set, SIGUSR1 );
    
act.sa_flags = 0;
act.sa_mask = set;
act.sa_handler = &handler;
sigaction( SIGUSR1, &act, NULL );


void handler( signo )
  {
    //Increment Time
  }   
   
   

   
