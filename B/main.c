#include <stdio.h> // traitement entrées/sortie
#include <stdlib.h>
#include <string.h> // traitement des chaines de caractère
#include <unistd.h>

#include "header.h"

int main()
{
	system("clear");
	FILE *f;		//création du pointeur vers le fichier
	char *ligne = malloc(sizeof(char) * 1024);	// création de la chaine de caractère qui stockera la ligne
	char *num0 = malloc(sizeof(char) * 300);
	char *num1 = malloc(sizeof(char) * 300);
	char *num2 = malloc(sizeof(char) * 300);
	char *num3 = malloc(sizeof(char) * 300);
	char *num4 = malloc(sizeof(char) * 300);
	char *num5 = malloc(sizeof(char) * 300);
	char *num6 = malloc(sizeof(char) * 300);
	char *num7 = malloc(sizeof(char) * 300);
	char *num8 = malloc(sizeof(char) * 300);
	char *num9 = malloc(sizeof(char) * 300);
	char *sep = malloc(sizeof(char) * 300);
	char *space = malloc(sizeof(char) * 100);
	char taille[200] = "";
	char type[10];	// création de la variable contenant le type de PBM
	char tampon[100] = "";
	int dimnum[2];	//création d'un tableau contenant les dimmensions du PBM
	int dim[2]; //création d'un tableau contenant les dimmensions de l'espace et :
	int *lignes = malloc(sizeof(int *)); // création du pointeur qui contiendra le nombre de lignes
	int *colonnes = malloc(sizeof(int *));	// création du pointeur qui contiendra le nombre de colonnes
	int n; // variable compteur (pour parcourir toute la ligne)
	int t;
	int k;
	int i;
	
	printf("Entrer le nombre de secondes avant refresh... ");
	scanf("%d", &t);
	
	printf("Entrer la taille de chiffre souhaitée... (default pour 5/3 ou sup pour 10/6)   ");
	fflush(stdout);
	fgets(taille, sizeof(taille), stdin);
	
	if(taille == "default")
	{
		k = 1;
	}
	else if(taille == "Default")
	{
		k = 1;
	}
	else if(taille == "DEFAULT")
	{
		k = 1;
	}
	else if(taille == "sup")
	{
		k = 2;
	}
	else if(taille == "Sup")
	{
		k = 2;
	}
	else if(taille == "SUP")
	{
		k = 2;
	}
	else
	{
		k = 1;
	}
	
	readPBM("../Test/0.pbm", dimnum, type, num0);	// on envoie les paramètres nécéssaires au module de lecture
	readPBM("../Test/1.pbm", dimnum, type, num1);	
	readPBM("../Test/2.pbm", dimnum, type, num2);	
	readPBM("../Test/3.pbm", dimnum, type, num3);
	readPBM("../Test/4.pbm", dimnum, type, num4);
	readPBM("../Test/5.pbm", dimnum, type, num5);	
	readPBM("../Test/6.pbm", dimnum, type, num6);
	readPBM("../Test/7.pbm", dimnum, type, num7);	
	readPBM("../Test/8.pbm", dimnum, type, num8);	
	readPBM("../Test/9.pbm", dimnum, type, num9);
	readPBM("../Test/sep.pbm", dimnum, type, sep);	
	readPBM("../Test/space.pbm", dim, type, space);	
	
	while(1)
	{
		taillefen(colonnes, lignes); // on appelle la fonction pour connaître la taille de la fenêtre

		assemblage(ligne, num0, num1, num2, num3, num4, num5, num6, num7, num8, num9, sep, space);

		centreVert(lignes, colonnes, dim[1], k);
		centreHor(colonnes, dim[0]);
		for(n=0;n<strlen(ligne);n++)
		{
			if(ligne[n] == '1')	// si on lit 1 dans le .pbm
			{
				printf("█");	// on affiche le caractère █
				if(*lignes >= 35 & *colonnes >=100 | k == 2)
				{
					printf("█");
					strcat(tampon,"██");
				}
			}
			else if(ligne[n] == '2') //sinon si on lit 2 dans le pbm
			{
				printf("\n"); // faire un retour à la ligne
				centreHor(colonnes, dim[0]);
				if(*lignes >= 35 & *colonnes >=100 | k == 2)
				{
					printf("%s\n",tampon);
					strcpy(tampon,"");
					centreHor(colonnes, dim[0]);
				}			
			}
			else	// sinon si on lit un 0 dans le .pbm
			{
				printf(" ");	// afficher un espace
				if(*lignes >= 35 & *colonnes >=100 | k == 2)
				{
					printf(" ");
					strcat(tampon,"  ");
				}
			}
		}
		centreVert(lignes, colonnes, dim[1], k);
		printf("Cet écran sera actualisé dans quelques secondes ");
		fflush(stdout);
		i = 0;
		while(i < t)
		{
			
			sleep(1);
			printf(". ");
			fflush(stdout);
			i++;
		}
		system("clear");

		/* DEBUG
		printf("\n");
		printf("Le fichier PBM est de type %s\n", type);
		printf("Largeur = %d Longueur = %d.\n", dim[0], dim[1]);
		printf("Ce terminal possède %d colonnes et %d lignes.\n", *colonnes, *lignes);*/
	}
	
	free(ligne);
	free(lignes);
	free(colonnes);
	free(num0);
	free(num1);
	free(num2);
	free(num3);
	free(num4);
	free(num5);
	free(num6);
	free(num7);
	free(num8);
	free(num9);
	free(sep);
	free(space);

	return 0;
}