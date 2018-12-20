#include <stdio.h>

#include "fast_mpd_parser/Include.h"

int main () {
	char* buffer = (char*) malloc(10000000 + 1);
	free(buffer);
	printf("Hello test\n");
	return 0;
}