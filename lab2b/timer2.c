#include <time.h>
#include "timer2.h"

#include <sys/siginfo.h>
#include <stdint.h>       /* for uintptr_t */
#include <hw/inout.h>     /* for in*() and out*() functions */
#include <sys/neutrino.h> /* for ThreadCtl() */
#include <sys/mman.h>     /* for mmap_device_io() */
#include <stdlib.h>
#include <stdio.h>

#define PORT_LENGTH 1
#define CTRL_ADDRESS 0x28B
#define DIOA_Address 0x288
#define DIOB_Address 0x289
#define CTRL_init 0x00 //DIO A & B as output

struct timespec delay_1;
struct timespec delay_2;
struct timespec remainder1;
struct timespec remainder2;
struct timespec waittime = {.tv_sec = 0, .tv_nsec = 100000000};
int PWM1;
int PWM2;

uintptr_t ctrl_reg;
uintptr_t portA;
uintptr_t portB;


void pin_init()
{
  ctrl_reg = mmap_device_io( PORT_LENGTH, CTRL_ADDRESS );
  out8( ctrl_reg, CTRL_init);
  
  portA = mmap_device_io( PORT_LENGTH, DIOA_Address); 
  portB = mmap_device_io( PORT_LENGTH, DIOB_Address);
}

void period_init()
{
	struct _clockperiod clkper;
	clkper.nsec = 10000;
	clkper.fract = 0;
	ClockPeriod(CLOCK_REALTIME, &clkper, NULL, 0);
}

void *servo1_thread(void *cmd)
{
  printf("servo1_thread start\n");
  //Starting Position
  servo1_delay(2000000); //10%
  while(1)
  {
    out8(portA, 0x01); //Set portA high
    
    //nanosleep for pulse width
    nanosleep(&delay_1, NULL);
    
    out8(portA, 0x00); //Set portA low
    
    //Set remaining wait to achieve a period of 20ms
    remainder1.tv_sec = 0;
    remainder1.tv_nsec = 20000000 - PWM1;

    //nanosleep remainder
    nanosleep(&remainder1, NULL);
  }
}

void *servo2_thread(void *cmd)
{
  printf("servo2_thread start\n");
  //Starting Position
  servo2_delay(2000000); //10%
  while(1)
  {
	//printf("portA High\n");
    out8(portB, 0x01);
    //nanosleep for pulse width
    nanosleep(&delay_2, NULL);
    out8(portB, 0x00);
   // printf("portA Low\n");
    //Set remaining wait to achieve a period of 20ms
    remainder2.tv_sec = 0;
    remainder2.tv_nsec = 20000000 - PWM2;
    
    //nanosleep remainder
    nanosleep(&remainder2, NULL);
  }
}

void *wait1_thread(void *cmd)
{
	wait_time1 = 0;
	while(1)
	{
		while(wait_time1 > 0)
		{
			nanosleep(&waittime, NULL);
			//printf("decrement wait count\n");
			wait_time1 --;
		}
	}
}

void *wait2_thread(void *cmd)
{
	wait_time2 = 0;
	while(1)
	{
		while(wait_time2 > 0)
		{
			nanosleep(&waittime, NULL);
			wait_time2 --;
		}
	}
}

void servo1_delay(int delay)
{
	PWM1 = delay;
	delay_1.tv_sec = 0;
	delay_1.tv_nsec = PWM1;
}

void servo2_delay(int delay)
{
	PWM2 = delay;
	delay_2.tv_sec = 0;
	delay_2.tv_nsec = PWM2;
}

