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
int parsePpmFile(FILE *fp);
FILE *seuillagePpmFile(void);
FILE *filtragePpmFile(void);
FILE *outputPpmFile(void);

// http://stackoverflow.com/questions/2693631/read-ppm-file-and-store-it-in-an-array-coded-with-c
int main(void) {
	FILE *ppmFileIn;
	FILE *ppmFileOut;

	// http://www.eclipse.org/forums/index.php/t/168233/
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	printf("%s-%03d: !!!Hello World!!!\n", __FILE__, __LINE__);
	printf("%s-%03d: read ppm file\n", __FILE__, __LINE__);
	ppmFileIn = readPpmFile();
	printf("%s-%03d: parse ppm file\n", __FILE__, __LINE__);
	parsePpmFile(ppmFileIn);
	//tabPixels = parsePpmFile(ppmFileIn);
	printf("%s-%03d: seuillage\n", __FILE__, __LINE__);
	//ppmFile = seuillagePpmFile();
	printf("%s-%03d: boucles de filtrage\n", __FILE__, __LINE__);
	//ppmFile = filtragePpmFile();
	printf("%s-%03d: ppm file output\n", __FILE__, __LINE__);
	//ppmFileOut = outputPpmFile();
	printf("%s-%03d: display ppm file output\n", __FILE__, __LINE__);
	//ppmFileOut = outputPpmFile();
	printf("%s-%03d: !!!That\'s all folks!!!\n", __FILE__, __LINE__);

	return EXIT_SUCCESS;

}

FILE *readPpmFile(void) {
	FILE *fp;
	char filename[100];
	printf("%s-%03d:   readPpmFile start\n", __FILE__, __LINE__);
	printf("%s-%03d:   Nom du fichier d\'entr�e?\n", __FILE__, __LINE__);
	scanf("%s", &filename);
	printf("%s-%03d:   Nom du fichier d\'entr�e: %s\n", __FILE__, __LINE__,
			filename);
	fp = fopen(filename, "rb");
	if (!fp) {
		fprintf(stderr, "Unable to open file '%s'\n", filename);
		exit(1);
	}
	printf("%s-%03d:   readPpmFile end\n", __FILE__, __LINE__);

	return fp;
}
int parsePpmFile(FILE *fp) {
	printf("%s-%03d:   parsePpmFile start\n", __FILE__, __LINE__);

	fclose(fp);
	printf("%s-%03d:   parsepmFile end\n", __FILE__, __LINE__);
	return 0;
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
