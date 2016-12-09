#include <stdio.h> // traitement entrées/sortie
#include <string.h> // traitement des chaines de caractère

int main()
{
	FILE *f;		//création du pointeur vers le fichier
	char ligne[100];	// création de la chaine de caractère qui stockera la ligne
	char type[10];	// création de la variable contenant le type de PBM
	char *tok = NULL; // création du token pour strtok
	int tab[2];	//création d'un tableau 
	int n; // variable pour parcourir toute la ligne

	f = fopen("test_coeur.pbm", "r");	// on met l'adresse du fichier dans le pointeur

	fgets(type, 10, f); // on rentre les "10" premiers caractères de la ligne actuelle de "f" dans "type" puis on passe à la ligne suivante
	type[strcspn(type, "\n")] = '\0';
	fgets(ligne, 15, f); // on rentre les dimmensions du pbm dans la chaine ligne

	tok = strtok(ligne, " ");	// on stocke la première dimmension (largeur) dans tok
	tab[0] = atoi(tok);	// conversion (atoi) du char en int puis stockage dans tab[0]
	tok = strtok(NULL, " "); // on stocke la deuxième dimmension (longueur) dans tok
	tab[1] = atoi(tok);	// conversion (atoi) du char en int puis stockage dans tab[1]

	while(fgets(ligne, 100, f) != NULL)	// tant que la ligne existe
	{
		for(n=0;n<strlen(ligne);n++) // ajouter 1 à n tant qu'il est inférieur au nombre de caractères dans la ligne
		{
			if(ligne[n] == '1') // si on lit 1 dans le .pbm
			{
				printf("#"); // on affiche le caractère #
			}
			else
			{
				printf(" "); // sinon afficher un espace
			}
		}
		printf("\n"); // retour à la ligne à la fin de chaque lignes
	}
	printf("Le fichier est PBM de type %s\n", type);
	printf("Largeur = %d Longueur = %d.\n", tab[0], tab[1]);

	fclose(f); // fermeture du fichier .pbm
	return 0;
}