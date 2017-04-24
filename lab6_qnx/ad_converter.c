#include <stdint.h>       /* for uintptr_t */
#include <hw/inout.h>     /* for in*() and out*() functions */
#include <sys/neutrino.h> /* for ThreadCtl() */
#include <sys/mman.h>     /* for mmap_device_io() */

define PORT_LENGTH 1
define base 0x280

uintptr_t wait_bit;
uintptr_t start_ad;
uintptr_t LSB;
uintptr_t MSB;

void ad_init ()
{
  //initialize the AD converter
  //For ±5V range (gain of 2), write 0x01 to Base + 3. 
}

void ad_converter ()
{
 //loop forever, re-running AD conversion 
 //Monitor the WAIT bit at Base + 3 bit 5.
 //When it is 1 the circuit is actively settling on the input signal.
 //start the A/D conversion by writing to Base + 0
 int i;
 for (i = 0; i < 10000; i++)
 {
  if !(inp(base+3) & 0x80) then break; // conversion completed
 }
  
}

void QNX_to_STM ()
{
  //send result of AD conversion to STM board
}
