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
	printf("%s-%03d:   Nom du fichier d\'entrée?\n", __FILE__, __LINE__);
	scanf("%s", &filename);
	printf("%s-%03d:   Nom du fichier d\'entrée: %s\n", __FILE__, __LINE__,
			filename);
	fp = fopen(filename, "rb");
	if (!fp) {
		fprintf(stderr, "%s-%03d: Unable to open file '%s'\n", __FILE__, __LINE__, filename);
		exit(1);
	}
	printf("%s-%03d:   readPpmFile end\n", __FILE__, __LINE__);

	return fp;
}
int parsePpmFile(FILE *fp) {
	char buff[16];

	printf("%s-%03d:   parsePpmFile start\n", __FILE__, __LINE__);
	//read image format
	if (!fgets(buff, sizeof(buff), fp)) {
		fprintf(stderr, "%s-%03d:   problem when reading file\n", __FILE__, __LINE__);
		exit(1);
	}

	//check the image format
	if (buff[0] != 'P' || buff[1] != '3') {
		printf("%s-%03d:   %c %c\n", __FILE__, __LINE__, buff[0], buff[1]);
		fprintf(stderr, "%s-%03d:   Invalid image format (must be 'P3')\n", __FILE__, __LINE__);
		exit(1);
	}
	else {
		printf("%s-%03d:   this is a P3 file\n", __FILE__, __LINE__);
	}

	//alloc memory form image
	img = (PPMImage *) malloc(sizeof(PPMImage));
	if (!img) {
		fprintf(stderr, "Unable to allocate memory\n");
		exit(1);
	}

	//check for comments
	c = getc(fp);
	while (c == '#') {
		while (getc(fp) != '\n')
			;
		c = getc(fp);
	}

	ungetc(c, fp);
	/*read image size information
	if (fscanf(fp, "%d %d", &img->x, &img->y) != 2) {
		fprintf(stderr, "Invalid image size (error loading '%s')\n", filename);
		exit(1);
	}

	//read rgb component
	if (fscanf(fp, "%d", &rgb_comp_color) != 1) {
		fprintf(stderr, "Invalid rgb component (error loading '%s')\n",
				filename);
		exit(1);
	}

	//check rgb component depth
	if (rgb_comp_color != RGB_COMPONENT_COLOR) {
		fprintf(stderr, "'%s' does not have 8-bits components\n", filename);
		exit(1);
	}

	while (fgetc(fp) != '\n')
		;
	//memory allocation for pixel data
	img->data = (PPMPixel*) malloc(img->x * img->y * sizeof(PPMPixel));

	if (!img) {
		fprintf(stderr, "Unable to allocate memory\n");
		exit(1);
	}

	//read pixel data from file
	if (fread(img->data, 3 * img->x, img->y, fp) != img->y) {
		fprintf(stderr, "Error loading image '%s'\n", filename);
		exit(1);
	}*/

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
