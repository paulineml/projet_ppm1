/*
 ============================================================================
 Name        : projet_ppm1.c
 Author      : Pauline Maury
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style

 ============================================================================
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define RGB_COMPONENT_COLOR 255
#define TOLERANCE_SEUIL 0.005f    //// différence minimum entre 2 seuils successifs

typedef struct {
	unsigned char red, green, blue;
} PPMPIXEL;

typedef struct {
	int x, y;
	PPMPIXEL *data;
} PPMIMAGE;


FILE *readPpmFile(void);
PPMIMAGE *parsePpmFile(FILE *fp);
FILE *seuillagePpmFile(void);
FILE *filtragePpmFile(void);
FILE *outputPpmFile(void);
void logImage(PPMIMAGE *img);

// fonctions prédéfinies pour indiquer si les données sont correctes
static void correct(void);
static void erreur_nbR(int nbR);
static void erreur_couleur(float couleur);
static void erreur_seuil(float seuil);
static void erreur_seuil_non_croissant(float s1, float s2);
static void erreur_seuil_non_distinct(float s1, float s2);


// http://stackoverflow.com/questions/2693631/read-ppm-file-and-store-it-in-an-array-coded-with-c

int main(void) {
	FILE *ppmFileIn;

	// cygwin stuff: http://www.eclipse.org/forums/index.php/t/168233/
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	printf("%s-%03d: !!!Hello World!!!\n", __FILE__, __LINE__);

	printf("%s-%03d: read ppm file\n", __FILE__, __LINE__);
	ppmFileIn = readPpmFile();
	printf("%s-%03d: parse ppm file\n", __FILE__, __LINE__);
	PPMIMAGE *img = parsePpmFile(ppmFileIn);
	logImage(img);
	static void correct(void);                                        //fonction du prof

	printf("%s-%03d: seuillage\n", __FILE__, __LINE__);
	FILE *seuillagePpmFile(void);  //ppmFile = seuillagePpmFile();

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

PPMIMAGE * parsePpmFile(FILE *fp) {
	char buff[16];
	int c, rgb_comp_color;
	PPMIMAGE *img;

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
	img = (PPMIMAGE *) malloc(sizeof(PPMIMAGE));
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

	printf("%s-%03d:   read rgb component\n", __FILE__, __LINE__);
	if (fscanf(fp, "%d", &rgb_comp_color) != 1) {
		static void erreur_couleur(float couleur);                              //fonction du prof
		fprintf(stderr, "%s-%03d:   Invalid rgb component (error loading')\n",
		__FILE__, __LINE__);
		exit(1);
	}

	printf("%s-%03d:   check rgb component depth\n", __FILE__, __LINE__);
	if (rgb_comp_color != RGB_COMPONENT_COLOR) {
		fprintf(stderr, "%s-%03d:   file does not have 8-bits components\n",
		__FILE__, __LINE__);
		static void erreur_nbR(int nbR)                                        //fonction du prof
		exit(1);
	}


	/*
	if seuil pas compris entre 0 et 1 {
	static void erreur_seuil(float seuil);
	}

	if si s1 > s2, ou s1 et s2 sont 2 seuils consécutifs {
	static void erreur_seuil_non_croissant(float s1, float s2);
	}


	if écart entre 2 seuils consécutifs est strictement inférieur à  la valeur TOLERANCE_SEUIL {
	static void erreur_seuil_non_distinct(float s1, float s2);
	}

*/


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

	while (fgetc(fp) != '\n')
		;
	printf("%s-%03d:   memory allocation for pixel data\n", __FILE__, __LINE__);
	img->data = (PPMPIXEL*) malloc(img->x * img->y * sizeof(PPMPIXEL));

	if (!img) {
		fprintf(stderr, "%s-%03d:   Unable to allocate memory\n", __FILE__,
		__LINE__);
		exit(1);
	}

	printf("%s-%03d:   read pixel data from P3 file\n", __FILE__, __LINE__);
	int red, green, blue;
	int i = 0;

	while (fscanf(fp, "%d %d %d", &red, &green, &blue) == 3) {
		img->data[i].red = red;
		img->data[i].green = green;
		img->data[i].blue = blue;
		/*printf("%s-%03d:   [%d] %d %d %d\n", __FILE__, __LINE__, i,
		 img->data[i].red, img->data[i].green, img->data[i].blue);*/
		i++;
	}

	fclose(fp);

	printf("%s-%03d:   parsepmFile end\n", __FILE__, __LINE__);
	return img;
}

FILE *seuillagePpmFile(void) {
	FILE *fp = 0;
	int i;
	int intensity;
	PPMIMAGE *img;

	printf("%s-%03d:   parsePpmFile start\n", __FILE__, __LINE__);
	for (i = 0; i < img->x * img->y; i++) {
		intensity = sqrt(
				(img->data[i].red * img->data[i].red)
						+ (img->data[i].green * img->data[i].green)
						+ (img->data[i].blue * img->data[i].blue));
		if (intensity < 0.3) {
			i = 0;
		} else if (intensity > 0.7) {
			i = 2;
		} else if (intensity == img->x) { //le seuil N°nbR est implicitement 1. et il est inclus dans le dernier intervalle
			i = 2;
		} else {
			i = 1;
		}
	}
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



void logImage(PPMIMAGE *img) {
	int i;

	printf("P3\n");
	printf("%d %d\n", img->x, img->y);
	printf("255\n");

	for (i = 0; i < img->x * img->y; i++) {
		printf("[%d,%d] %d %d %d\n", i % img->y, i / img->y, img->data[i].red,
				img->data[i].green, img->data[i].blue);
	}
}





 // A appeler si toutes les données sont correctes (rendu intermédiaire)
static void correct(void)
{
	printf("Les données sont correctes ! \n");
}

//----------------------------------------------------
static void erreur_nbR(int nbR)
{
	printf("Nombre de couleurs incorrect [2,255]: %d\n",nbR);
	exit(EXIT_FAILURE);
}

//----------------------------------------------------
static void erreur_couleur(float couleur)
{
	printf("Valeur R-V-B incorrecte [0., 1.]: %6.3f\n",couleur);
	exit(EXIT_FAILURE);
}

//----------------------------------------------------
static void erreur_seuil(float seuil)
{
	printf("Valeur de seuil incorrecte ]0., 1.[: %6.3f\n",seuil);
	exit(EXIT_FAILURE);
}


//-------------------------------------------------------------
// A appeler si s1 > s2, ou s1 et s2 sont 2 seuils consécutifs
static void erreur_seuil_non_croissant(float s1, float s2)
{
	printf("Valeurs de seuils non croissantes: %5.3f > %5.3f\n", s1, s2);

	exit(EXIT_FAILURE);
}


//---------------------------------------------------------------
// A appeler si l'écart entre 2 seuils consécutifs est strictement inférieur à  la valeur TOLERANCE_SEUIL
static void erreur_seuil_non_distinct(float s1, float s2)
{
	printf("Valeur de seuil trop proche du précédent [%5.3f]:"
	       " %5.6f et %5.6f\n",TOLERANCE_SEUIL, s1, s2);

	exit(EXIT_FAILURE);
}


