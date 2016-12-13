#include <stdio.h> // traitement entrées/sortie
#include <stdlib.h>
#include <string.h> // traitement des chaines de caractère

#include "header.h"

int main()
{
	system("clear");
	FILE *f;		//création du pointeur vers le fichier
	char *ligne = malloc(sizeof(char) * 1024);	// création de la chaine de caractère qui stockera la ligne
	char type[10];	// création de la variable contenant le type de PBM
	char tampon[100];
	int dim[2];	//création d'un tableau
	int *lignes = malloc(sizeof(int *)); // création du pointeur qui contiendra le nombre de lignes
	int *colonnes = malloc(sizeof(int *));	// création du pointeur qui contiendra le nombre de colonnes
	int n; // variable compteur (pour parcourir toute la ligne)

	taillefen(colonnes, lignes); // on appelle la fonction pour connaître la taille de la fenêtre

	readPBM("test_coeur.pbm", dim, type, ligne);	// on envoie les paramètres nécéssaires au module de lecture

	centre(colonnes, dim[0]);
	for(n=0;n<strlen(ligne);n++)
	{
		if(ligne[n] == '1')	// si on lit 1 dans le .pbm
		{
			printf("█");	// on affiche le caractère █
			if(*lignes >= 35 & *colonnes >=100)
			{
				printf("█");
				strcat(tampon,"██");
			}
		}
		else if(ligne[n] == '2') //sinon si on lit 2 dans le pbm
		{
			printf("\n"); // faire un retour à la ligne
			if(*lignes >= 35 & *colonnes >=100)
			{
				printf("%s\n",tampon);
				strcpy(tampon,"");
			}
		}
		else	// sinon si on lit un 0 dans le .pbm
		{
			printf(" ");	// afficher un espace
			if(*lignes >= 35 & *colonnes >=100)
			{
				printf(" ");
				strcat(tampon,"  ");
			}
		}
	}
	centre(colonnes, dim[0]);

	/*printf("\n");
	printf("Le fichier PBM est de type %s\n", type);
	printf("Largeur = %d Longueur = %d.\n", dim[0], dim[1]);
	printf("Ce terminal possède %d colonnes et %d lignes.\n", *colonnes, *lignes);*/

	free(lignes);
	free(colonnes);
	return 0;
}