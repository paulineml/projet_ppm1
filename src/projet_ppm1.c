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

typedef struct {
	unsigned char red, green, blue;
} PPMPixel;

typedef struct {
	int x, y;
	PPMPixel *data;
} PPMImage;

#define RGB_COMPONENT_COLOR 255

FILE *readPpmFile(void);
PPMImage * parsePpmFile(FILE *fp);
FILE *seuillagePpmFile(void);
FILE *filtragePpmFile(void);
FILE *outputPpmFile(void);
void logImage(PPMImage *img);

// http://stackoverflow.com/questions/2693631/read-ppm-file-and-store-it-in-an-array-coded-with-c
int main(void) {
	FILE *ppmFileIn;

	// http://www.eclipse.org/forums/index.php/t/168233/
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	printf("%s-%03d: !!!Hello World!!!\n", __FILE__, __LINE__);
	printf("%s-%03d: read ppm file\n", __FILE__, __LINE__);
	ppmFileIn = readPpmFile();
	printf("%s-%03d: parse ppm file\n", __FILE__, __LINE__);
	PPMImage *img = parsePpmFile(ppmFileIn);
	logImage(img);
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
	scanf("%s", filename);
	printf("%s-%03d:   Nom du fichier d\'entrée: %s\n", __FILE__, __LINE__,
			filename);
	fp = fopen(filename, "r");
	if (!fp) {
		fprintf(stderr, "%s-%03d: Unable to open file '%s'\n", __FILE__,
		__LINE__, filename);
		exit(1);
	}
	printf("%s-%03d:   readPpmFile end\n", __FILE__, __LINE__);

	return fp;
}

PPMImage * parsePpmFile(FILE *fp) {
	char buff[16];
	int c, rgb_comp_color;
	PPMImage *img;

	printf("%s-%03d:   parsePpmFile start\n", __FILE__, __LINE__);

	printf("%s-%03d:   read image format\n", __FILE__, __LINE__);
	if (!fgets(buff, sizeof(buff), fp)) {
		fprintf(stderr, "%s-%03d:   problem when reading file\n", __FILE__,
		__LINE__);
		exit(1);
	}

	printf("%s-%03d:   check the image format\n", __FILE__, __LINE__);
	if (buff[0] != 'P' || buff[1] != '3') {
		printf("%s-%03d:   %c %c\n", __FILE__, __LINE__, buff[0], buff[1]);
		fprintf(stderr, "%s-%03d:   Invalid image format (must be 'P3')\n",
		__FILE__, __LINE__);
		exit(1);
	} else {
		printf("%s-%03d:   this is a P3 file\n", __FILE__, __LINE__);
	}

	printf("%s-%03d:   alloc memory form image\n", __FILE__, __LINE__);

	img = (PPMImage *) malloc(sizeof(PPMImage));
	if (!img) {
		fprintf(stderr, "%s-%03d:   Unable to allocate memory\n", __FILE__,
		__LINE__);
		exit(1);
	}

	printf("%s-%03d:   check for comments\n", __FILE__, __LINE__);
	c = getc(fp);
	while (c == '#') {
		while (getc(fp) != '\n')
			;
		c = getc(fp);
	}

	ungetc(c, fp);
	printf("%s-%03d:   read image size information\n", __FILE__, __LINE__);
	if (fscanf(fp, "%d %d", &img->x, &img->y) != 2) {
		fprintf(stderr, "%s-%03d:   Invalid image size (error loading)\n",
		__FILE__, __LINE__);
		exit(1);
	} else {
		printf("%s-%03d:   col: %d, row: %d\n", __FILE__, __LINE__, img->x,
				img->y);
	}

	printf("%s-%03d:   read rgb component\n", __FILE__, __LINE__);
	if (fscanf(fp, "%d", &rgb_comp_color) != 1) {
		fprintf(stderr, "%s-%03d:   Invalid rgb component (error loading')\n",
		__FILE__, __LINE__);
		exit(1);
	}

	printf("%s-%03d:   check rgb component depth\n", __FILE__, __LINE__);
	if (rgb_comp_color != RGB_COMPONENT_COLOR) {
		fprintf(stderr, "%s-%03d:   file does not have 8-bits components\n",
		__FILE__, __LINE__);
		exit(1);
	}

	while (fgetc(fp) != '\n')
		;
	printf("%s-%03d:   memory allocation for pixel data\n", __FILE__, __LINE__);
	img->data = (PPMPixel*) malloc(img->x * img->y * sizeof(PPMPixel));

	if (!img) {
		fprintf(stderr, "%s-%03d:   Unable to allocate memory\n", __FILE__,
		__LINE__);
		exit(1);
	}

	printf("%s-%03d:   read pixel data from P3 file\n", __FILE__, __LINE__);
	/* P6 (binary) if (fread(img->data, 3 * img->x, img->y, fp) != img->y) {
	 fprintf(stderr, "%s-%03d:   Error loading image\n", __FILE__,
	 __LINE__);
	 exit(1);
	 }*/
	int red, green, blue;
	int i = 0;

	while (fscanf(fp, "%d %d %d", &red, &green, &blue) == 3) {
		img->data[i].red = red;
		img->data[i].green = green;
		img->data[i].blue = blue;
		printf("%s-%03d:   [%d] %d %d %d\n", __FILE__, __LINE__, i,
				img->data[i].red, img->data[i].green, img->data[i].blue);
		i++;
	}

	fclose(fp);
	printf("%s-%03d:   parsepmFile end\n", __FILE__, __LINE__);
	return img;
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

void logImage(PPMImage *img) {
	int i;

	printf("P3\n");
	printf("%d %d\n", img->x, img->y);
	printf("255\n");

	/*for (x = 0; x < img->x; x+=3);
	 {
	 for (y = 0; y < img->y; y++);

	 {
	 printf("%d %d %d\n", img->data[x].red, img->data[x].green, img->data[x].blue);
	 }
	 }*/
	for (i = 0; i < img->x * img->y; i++) {
		printf("[%d,%d] %d %d %d\n", i % img->y, i / img->y, img->data[i].red,
				img->data[i].green, img->data[i].blue);
	}
}
