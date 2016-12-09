#include <stdio.h> // traitement entrées/sortie
#include <string.h> // traitement des chaines de caractère

int main()
{
	FILE *f;		//création du pointeur vers le fichier
	char ligne[100];	// création de la chaine de caractère qui stockera la ligne
	int n; // variable pour parcourir toute la ligne

	f = fopen("test_coeur.pbm", "r");	// on met l'adresse du fichier dans le pointeur

	while(fgets(ligne, 100, f) != NULL)	// tant que la ligne existe
	{
		for(n=0;n<strlen(ligne);n++) // ajouter 1 à n tant qu'il est inférieur au nombre de caractères dans la ligne
		{
			if(ligne[n] == '1') // si on lit 1 dans le .pbm
			{
				printf("%c", 219); // on affiche le caractère ASCII 219
			}
			else
			{
				printf(" "); // sinon afficher un espace
			}
		}
		printf("\n"); // retour à la ligne à la fin de chaque lignes
	}

	fclose(f); // fermeture du fichier .pbm
	return 0;
}

// mettre 2 if cote a cote pour les 2 chiffres