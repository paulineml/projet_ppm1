/*
	File : recolor.c
	Nom    : Maury Laribière
	Prenom : Pauline
	CAMIPRO: 26491
	Date   : 18.10.2014
	Version code: 1.00
	Version de la donnée: 1.03
	Description : projet recolor. lit une table de couleurs
	 et des seuils pour transformer une image en format ppm
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    unsigned char red, green, blue;
} PpmPixel;

typedef struct 
{
    int x, y;
    PpmPixel *data;
} PpmImage;

#define TOLERANCE_SEUIL 0.005f
#define FAUX 0
#define RVB 3
#define R 0
#define V 1
#define B 2
#define COULEUR_MIN 2
#define COULEUR_MAX 255

FILE *readPpmFile(void);
PpmImage * parsePpmFile(FILE *fp);
PpmImage * seuillagePpmFile(PpmImage *img);
FILE *filtragePpmFile(void);
FILE *outputPpmFile(void);
void logImage(PpmImage *img);

static void correct(void);
static void erreur_nbR(int nbR);
static void erreur_couleur(float couleur);
static void erreur_seuil(float seuil);
static void erreur_seuil_non_distinct(float s1, float s2);
static void erreur_seuil_non_croissant(float s1, float s2);

//-------------------------------------------------------------------
int verbose;

int main(void) {
    FILE *ppmFileIn;
    PpmImage *img;

    printf("%s-%03d: !!!Hello World!!!\n", __FILE__, __LINE__);
    printf("%s-%03d: read ppm file\n", __FILE__, __LINE__);
    ppmFileIn = readPpmFile();
    printf("%s-%03d: parse ppm file\n", __FILE__, __LINE__);
    img = parsePpmFile(ppmFileIn);
    logImage(img);
    printf("%s-%03d: seuillage\n", __FILE__, __LINE__);
    img = seuillagePpmFile(img);
    printf("%s-%03d: boucles de filtrage\n", __FILE__, __LINE__);
    //ppmFile = filtragePpmFile();
    printf("%s-%03d: display ppm file output\n", __FILE__, __LINE__);
    //ppmFileOut = outputPpmFile();
    printf("%s-%03d: !!!That\'s all folks!!!\n", __FILE__, __LINE__);

    return EXIT_SUCCESS;

}

FILE *readPpmFile(void) 
{
    FILE *fp;
    char filename[100];
    printf("%s-%03d:   readPpmFile start\n", __FILE__, __LINE__);
    printf("%s-%03d:   Nom du fichier d\'entrée?\n", __FILE__, __LINE__);
    scanf("%s", filename);
    printf("%s-%03d:   Nom du fichier d\'entrée: %s\n", __FILE__, __LINE__,
            filename);
    fp = fopen(filename, "r");
    printf("%s-%03d:   readPpmFile end\n", __FILE__, __LINE__);

    return fp;
}

PpmImage * parsePpmFile(FILE *fp) 
{
    PpmImage *img;
    int red, green, blue;

    printf("%s-%03d:   parsePpmFile start\n", __FILE__, __LINE__);
    printf("%s-%03d:   Entrer le mode verbose oui: 1, non: 0\n", __FILE__, __LINE__);
    scanf("%d", &verbose);
    printf("%s-%03d:   verbose: %d\n", __FILE__, __LINE__,verbose);
	if(verbose!=FAUX) 
	{
		printf("%s-%03d:   Entrer le nombre de couleurs de recoloriage\n", __FILE__, __LINE__);
	}
	int nbR;
	scanf("%d", &nbR); 

	/*Test 2 : Nombre de couleur incorrect */
	if(nbR<COULEUR_MIN || nbR>COULEUR_MAX)
	{
		erreur_nbR(nbR);
	}
	
	if(verbose!=FAUX) 
	{
	printf("Entrer les %d couleurs de recoloriage\n", nbR);
	}
	float tab_nbR[nbR][RVB];
	int i;
	for(i=0; i<nbR; i++)
	{
		scanf("%f %f %f", &tab_nbR[i][R],&tab_nbR[i][V],&tab_nbR[i][B]);
		
		/*Test 3 : Valeur RVB incorrecte*/
		if(tab_nbR[i][R]<0 || tab_nbR[i][R]>1)
		{
			erreur_couleur(tab_nbR[i][R]);
		}
		if(tab_nbR[i][V]<0 || tab_nbR[i][V]>1)
		{
			erreur_couleur(tab_nbR[i][V]);
		}
		if(tab_nbR[i][B]<0 || tab_nbR[i][B]>1)
		{
			erreur_couleur(tab_nbR[i][B]);
		}
	}
	
	if(verbose!=FAUX) 
	{
		printf("Entrer les %d seuils de recoloriage\n", nbR-1);
	}
	
	float tab_seuils[nbR-1];
	for(i=0; i<nbR-1; i++)
	{
		scanf("%f", &tab_seuils[i]);
		
		/*Test 4 : Valeur de seuils incorrect*/
		if(tab_seuils[i]<=0 || tab_seuils[i]>=1)
		{
			erreur_seuil(tab_seuils[i]);
		}
		
		/*Test 6 : Valeur de seuil non croissant*/
		if(tab_seuils[i-1]>tab_seuils[i])
		{
			erreur_seuil_non_croissant(tab_seuils[i-1], tab_seuils[i]);
		}
		
		/*Test 5 : Valeur de seuils trop proches du précédent*/
		if((tab_seuils[i]-tab_seuils[i-1])<TOLERANCE_SEUIL)
		{
			erreur_seuil_non_distinct(tab_seuils[i-1],tab_seuils[i]);
		}
	}
	
	
	if(verbose!=FAUX) 
	{
		printf("%s-%03d:   Entrer le nombre de contrastes\n", __FILE__, __LINE__);
	}
	int nbF;
	scanf("%d", &nbF);
	//*nbFiltrage = nbF;
	
	if(verbose!=FAUX)  
	{
		printf("%s-%03d:   Entrer le format de l'image\n", __FILE__, __LINE__);
	}
	char format[3];
	scanf("%s", format);
	
	if(verbose!=FAUX) 
	{
		printf("%s-%03d:   Entrer les dimensions de l'image\n", __FILE__, __LINE__);
	}
	int nbC;
	int nbL;
	scanf("%d %d", &nbC, &nbL);
	
	if(verbose!=FAUX) 
	{
		printf("%s-%03d:   Entrer l'intensité maximum de la couleur\n", __FILE__, __LINE__);
	}
	int intensite;
	scanf("%d", &intensite);
	
	if(verbose!=FAUX) 
	{
		printf("%s-%03d:   Entrer les valeurs des couleurs des pixels\n", __FILE__, __LINE__);
	}
	float tab_pixels[nbL][nbC*RVB];
	int j;
	for(i=0; i<nbL; i++)
	{
		for(j=0; j<nbC*RVB; j++)
		{
		scanf("%f", &tab_pixels[i][j]);
		}
	}
	
	correct();

    printf("%s-%03d:   alloc memory form image\n", __FILE__, __LINE__);
    img = (PpmImage *) malloc(sizeof(PpmImage));

    
    while (fgetc(fp) != '\n') //tant que on lit un espace, on continue
        ;
    printf("%s-%03d:   memory allocation for pixel data\n", __FILE__, __LINE__);
    img->data = (PpmPixel*) malloc(img->x * img->y * sizeof(PpmPixel));



    while (fscanf(fp, "%d %d %d", &red, &green, &blue) == 3) 
    {
        img->data[i].red = red;
        img->data[i].green = green;
        img->data[i].blue = blue;
     
        i++;
    }

    fclose(fp);
    printf("%s-%03d:   parsePmFile end\n", __FILE__, __LINE__);
    return img;
}

PpmImage *seuillagePpmFile(PpmImage *img) 
{
    int i;
    int intensity;
 
    
    printf("%s-%03d:   seuillageFile start\n", __FILE__, __LINE__);
    for(i=0; i<img->x * img->y; i++) 
    {
		intensity = sqrt(
			(img->data[i].red * img->data[i].red)
			+ (img->data[i].green * img->data[i].green)
			+ (img->data[i].blue * img ->data[i].blue));
		if(intensity<0.3)
		{
			i=0;
		}
		else if(intensity > 0.7)
		{
			i=2;
		}
		else if(intensity == img->x)
		{
			i=2;
		}
		else 
		{
			i=1;
		}
	}
 
    printf("%s-%03d:   seuillageFile end\n", __FILE__, __LINE__);
    return img;
}

FILE *filtragePpmFile(void) 
{
    FILE *fp = 0;
    //int i;
    //int *nbFiltrage;
    
    printf("%s-%03d:   filtragePpmFile start\n", __FILE__, __LINE__);
    //for(i=0; i<*nbFiltrage; i++);
    
    printf("%s-%03d:   filtragepmFile end\n", __FILE__, __LINE__); 
    return fp;
}   

FILE *outputPpmFile(void) 
{
    FILE *fp = 0;
    printf("%s-%03d:   outputPpmFile start\n", __FILE__, __LINE__);
    
    
    
    printf("%s-%03d:   outputpmFile end\n", __FILE__, __LINE__);
    return fp;
}

void logImage(PpmImage *img) 
{
    int i;

    printf("P3\n");
    printf("%d %d\n", img->x, img->y);
    printf("255\n");

    for (i = 0; i < img->x * img->y; i++) 
    {
        printf("[%d,%d] %d %d %d\n", i % img->y, i / img->y, img->data[i].red,
                img->data[i].green, img->data[i].blue);
    }
}




//---------------------------------------------------------------------
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
// A appeler si s1 > s2, où s1 et s2 sont 2 seuils consécutifs
static void erreur_seuil_non_croissant(float s1, float s2)
{
	printf("Valeurs de seuils non croissantes: %5.3f > %5.3f\n", s1, s2);
		   
	exit(EXIT_FAILURE);
}

//---------------------------------------------------------------
// A appeler si l'écart entre 2 seuils consécutifs est strictement 
// inférieur à la valeur TOLERANCE_SEUIL
static void erreur_seuil_non_distinct(float s1, float s2)
{
	printf("Valeur de seuil trop proche du précédent [%5.3f]:"
	       " %5.6f et %5.6f\n",TOLERANCE_SEUIL, s1, s2);
		   
	exit(EXIT_FAILURE);
}

