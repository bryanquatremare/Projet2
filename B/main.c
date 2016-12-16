#include <stdio.h> // traitement entrées/sortie
#include <stdlib.h>
#include <string.h> // traitement des chaines de caractère
#include <unistd.h>

#include "header.h"

int main()
{
	system("clear");
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
	char path[256];
	char path2[256];
	char taille[200];
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
	
	if(!(getenv("EXIASAVER2_SLEEP") == NULL))
	{
		t = atoi(getenv("EXIASAVER2_SLEEP"));
	}
	else
	{
		t = 10;
	}
	
	if(!(getenv("EXIASAVER2_TAILLE") == NULL))
	{
		strcpy(taille, getenv("EXIASAVER2_TAILLE"));
	}
	else
	{
		strcpy(taille, "default");
	}

	if(!(getenv("EXIASAVER2_PBM") == NULL))
	{
		strcpy(path, getenv("EXIASAVER2_PBM"));
		strcpy(path2, getenv("EXIASAVER2_PBM"));
	}
	else
	{
		strcpy(path, ".");
		strcpy(path2, ".");
	}
	
	if(strcmp(taille, "default") == 0) // compare la variable taille à plusieurs autres possibilitées de char et agit en conséquence "k = 1" equivaut au format de base des caractères et "k = 2" équivaut au format 10 par 6
	{
		k = 1;
	}
	else if(strcmp(taille, "Default") == 0)
	{
		k = 1;
	}
	else if(strcmp(taille, "DEFAULT") == 0)
	{
		k = 1;
	}
	else if(strcmp(taille, "sup") == 0)
	{
		k = 2;
	}
	else if(strcmp(taille, "Sup") == 0)
	{
		k = 2;
	}
	else if(strcmp(taille, "SUP") == 0)
	{
		k = 2;
	}
	else
	{
		k = 1;
	}
	
	sprintf(path2, "%s/0.pbm", path);
	readPBM(path2, dimnum, type, num0);	// on envoie les paramètres nécéssaires au module de lecture
	sprintf(path2, "%s/1.pbm", path);
	readPBM(path2, dimnum, type, num1);
	sprintf(path2, "%s/2.pbm", path);	
	readPBM(path2, dimnum, type, num2);
	sprintf(path2, "%s/3.pbm", path);	
	readPBM(path2, dimnum, type, num3);
	sprintf(path2, "%s/4.pbm", path);
	readPBM(path2, dimnum, type, num4);
	sprintf(path2, "%s/5.pbm", path);
	readPBM(path2, dimnum, type, num5);
	sprintf(path2, "%s/6.pbm", path);	
	readPBM(path2, dimnum, type, num6);
	sprintf(path2, "%s/7.pbm", path);
	readPBM(path2, dimnum, type, num7);
	sprintf(path2, "%s/8.pbm", path);	
	readPBM(path2, dimnum, type, num8);
	sprintf(path2, "%s/9.pbm", path);	
	readPBM(path2, dimnum, type, num9);
	sprintf(path2, "%s/sep.pbm", path);
	readPBM(path2, dimnum, type, sep);
	sprintf(path2, "%s/space.pbm", path);	
	readPBM(path2, dim, type, space);	
	
	while(1) //le programme s'execute jusqu'à ce qu'il soit kill par ^c
	{
		taillefen(colonnes, lignes); // on appelle la fonction pour connaître la taille de la fenêtre

		assemblage(ligne, num0, num1, num2, num3, num4, num5, num6, num7, num8, num9, sep, space); //On assemble les différents numéros et caractères dans une seule chaîne de caractère selon l'heure
		assemblage(ligne, num0, num1, num2, num3, num4, num5, num6, num7, num8, num9, sep, space);
		assemblage(ligne, num0, num1, num2, num3, num4, num5, num6, num7, num8, num9, sep, space);

		centreVert(lignes, colonnes, dim[1], k); //ajout de sauts de lignes au dessus de l'heure affichée
		centreHor(colonnes, dim[0]); //ajout d'espaces au début de l'heure affichée pour centrage horizontal
		for(n=0;n<strlen(ligne);n++) //fonction qui affiche l'heure à partir de la chaine de caractère crée dans assemblage
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
		centreVert(lignes, colonnes, dim[1], k); // ajout de saut de ligne après l'affichage de l'heure
		printf("Cet écran sera actualisé dans quelques secondes ");
		fflush(stdout); //oblige le programme à afficher la sortie
		i = 0;
		while(i < t) //tant que le temps avant actualisation entré par l'utilisateur n'est pas écoulé
		{
			sleep(1);
			printf(".");
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
	
	free(ligne); //libération des espaces réservés aux pointeurs
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