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
