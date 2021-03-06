#include <stdint.h>       /* for uintptr_t */
#include <hw/inout.h>     /* for in*() and out*() functions */
#include <sys/neutrino.h> /* for ThreadCtl() */
#include <sys/mman.h>     /* for mmap_device_io() */
#include <stdio.h>
#include "ad_converter.h"

#define PORT_LENGTH 1
#define base 0x280
#define CTRL_init 0x00 //DIO A & B as output
#define CTRL_ADDRESS 0x28B
#define DIOA_Address 0x288
#define DIOB_Address 0x289

int16_t LSB;
int16_t MSB;
int16_t Data;

uintptr_t wait_bit;
uintptr_t start_ad;
uintptr_t input_channel;
uintptr_t interrupt;
uintptr_t ctrl_reg;
uintptr_t portA;
uintptr_t portB;

void ad_init () //Run at start
{
	wait_bit = mmap_device_io(PORT_LENGTH, (base + 3));
	start_ad = mmap_device_io(PORT_LENGTH, (base));
	interrupt = mmap_device_io(PORT_LENGTH, (base + 4));
	input_channel = mmap_device_io(PORT_LENGTH, (base + 2));
	ctrl_reg = mmap_device_io( PORT_LENGTH, CTRL_ADDRESS );
	portA = mmap_device_io( PORT_LENGTH, DIOA_Address);
	portB = mmap_device_io( PORT_LENGTH, DIOB_Address);

	out8(ctrl_reg, CTRL_init); //Set ports A and B as output
	out8(interrupt, 0x00); //Disable Interrupts
	out8(input_channel, 0x44); //Select Channel 4
	out8(wait_bit, 0x00); //Set �10V range
	out8(portA, 0x02); //for debugging. Used to find A0 and A1
}

void ad_converter () //Thread
{
	//loop forever, re-running AD conversion
	while(1)
	{
		if(!(in8(wait_bit) & 0x20)) //Check if AD circuit is settled (bit 5)
		{
			out8(start_ad, 0x80);
			if(checkstatus())
			{
				QNX_to_STM();
			}
			else
			{
				//output error?
				printf("AD Conversion Error\n");
			}
		}
	}
}

int checkstatus()
{
	int i;
	for (i = 0; i < 10000; i++)
	{
		if (!(in8(wait_bit) & 0x80)) return(1); // conversion completed
	}
	return(-1); //Conversion didn't complete
}

void QNX_to_STM () 
{
	float voltage = 0;
	int pos = 0;
	//send result of AD conversion to STM board
	LSB = in8(base);
	MSB = in8(base + 1);
	Data = MSB * 256 + LSB; //Use to display voltage?

	voltage =  Data / (float)32768 * 10;

	pos = (int)((voltage + 10) * 12.75);;

	out8(portA, pos);
	if ((pos < 63 || pos > 188)) {
		printf("Voltage out of range error\n");
	}
}
