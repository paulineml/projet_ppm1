/*
 ============================================================================
 Name        : projet_ppm1.c
 Author      : Pauline Maury
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int i = 0;
	printf("!!!Hello World!!! %s-%d\n", __FILE__, __LINE__);
	printf("line %d i: %d\n", __LINE__, i);
	i++;
	printf("line %d i: %d\n", __LINE__, i);
	printf("!!!That\'s all folks!!! line %d\n", __LINE__);
	return EXIT_SUCCESS;
}
