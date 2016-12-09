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
	type[strcspn(type, "\n")] = '\0'; // On supprime le retour à la ligne de la fin de ligne
	fgets(ligne, 15, f); // on rentre les dimmensions du pbm dans la chaine ligne

	tok = strtok(ligne, " ");	// on stocke la première dimmension (largeur) dans tok
	tab[0] = atoi(tok);	// conversion (atoi) du char en int puis stockage dans tab[0]
	tok = strtok(NULL, " "); // on stocke la deuxième dimmension (longueur) dans tok
	tab[1] = atoi(tok);	// conversion (atoi) du char en int puis stockage dans tab[1]

		while(fgets(ligne, 100,f)!= NULL) // tant que la ligne existe
		{
			tok = strtok(ligne, " "); // découpage du premier morceau jusqu'au séparateur (" ") (permet la suppression des espace)
			while(tok != NULL)	// tant que le token n'est pas vide (tant qu'on a pas atteint la fin de la ligne)
    		{
				if(!(strncmp(tok, "1", 1))) // si on lit 1 dans le .pbm
				{
					printf("#");	// on affiche le caractère #
				}
				else	// si on lit un 0 dans le .pbm
				{
					printf(" ");	// sinon afficher un espace
				}
				tok = strtok(NULL, " "); // on passe au token suivant
			}
			printf("\n");	// retour à la ligne à la fin de chaque lignes
		}

	printf("Le fichier PBM est de type %s\n", type);
	printf("Largeur = %d Longueur = %d.\n", tab[0], tab[1]);

	fclose(f); // fermeture du fichier .pbm
	return 0;
}