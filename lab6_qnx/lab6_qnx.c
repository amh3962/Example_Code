#include <stdlib.h>
#include <stdio.h>
#include "ad_converter.h"

int main(int argc, char *argv[]) {
	printf("Lab6 - Yura Kim, Aaron Halling\n");

	// Initialize
	ad_init();

	// Run AD converter
	ad_converter();

	return EXIT_SUCCESS;
}
