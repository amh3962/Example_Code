/*
Real Time and Embedded Systems - Lab6
Yura Kim
Aaron Halling

Objective: Measure the output of a signal generator with a A/D converter using a QNX Neutrino program.
Transfer the result to a STM32 development board to then convert the result into a servo posistion.

*See Project6.pdf for complete description and requirements*
*/
#include <stdlib.h>
#include <stdio.h>
#include "ad_converter.h"
#include <sys/neutrino.h>

int main(int argc, char *argv[]) {
	printf("Lab6 - Yura Kim, Aaron Halling\n");

	// Initialize
	ThreadCtl( _NTO_TCTL_IO, NULL );
	ad_init();


	// Run AD converter
	ad_converter();

	return EXIT_SUCCESS;
}
