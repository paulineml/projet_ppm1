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

FILE *readPpmFile(void);
FILE *parsePpmFile(void);
FILE *seuillagePpmFile(void);
FILE *filtragePpmFile(void);
FILE *outputPpmFile(void);

int main(void) {
	FILE *ppmFile;

	printf("%s-%03d: !!!Hello World!!!\n", __FILE__, __LINE__);
	printf("%s-%03d: read ppm file\n", __FILE__, __LINE__);
	ppmFile = readPpmFile();
	printf("%s-%03d: parse ppm file\n", __FILE__, __LINE__);
	ppmFile = parsePpmFile();
	printf("%s-%03d: seuillage\n", __FILE__, __LINE__);
	ppmFile = seuillagePpmFile();
	printf("%s-%03d: boucles de filtrage\n", __FILE__, __LINE__);
	ppmFile = filtragePpmFile();
	printf("%s-%03d: ppm file output\n", __FILE__, __LINE__);
	ppmFile = outputPpmFile();
	printf("%s-%03d: !!!That\'s all folks!!!\n", __FILE__, __LINE__);

	return EXIT_SUCCESS;


}

FILE *readPpmFile(void) {
	FILE *fp = 0;
	printf("%s-%03d:   readPpmFile start\n", __FILE__, __LINE__);
	printf("%s-%03d:   readPpmFile end\n", __FILE__, __LINE__);
	return fp;
}
FILE *parsePpmFile(void) {
	FILE *fp = 0;
	printf("%s-%03d:   parsePpmFile start\n", __FILE__, __LINE__);
	printf("%s-%03d:   parsepmFile end\n", __FILE__, __LINE__);
	return fp;
}
FILE *seuillagePpmFile(void) {
	FILE *fp = 0;
	printf("%s-%03d:   parsePpmFile start\n", __FILE__, __LINE__);
	printf("%s-%03d:   parsepmFile end\n", __FILE__, __LINE__);
	return fp;
}
FILE *filtragePpmFile(void) {
	FILE *fp = 0;
	printf("%s-%03d:   parsePpmFile start\n", __FILE__, __LINE__);
	printf("%s-%03d:   parsepmFile end\n", __FILE__, __LINE__);
	return fp;
}
FILE *outputPpmFile(void) {
	FILE *fp = 0;
	printf("%s-%03d:   parsePpmFile start\n", __FILE__, __LINE__);
	printf("%s-%03d:   parsepmFile end\n", __FILE__, __LINE__);
	return fp;
}
