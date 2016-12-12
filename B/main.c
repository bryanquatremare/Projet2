#include <stdio.h> // traitement entrées/sortie
#include <stdlib.h>
#include <string.h> // traitement des chaines de caractère
#include <sys/ioctl.h> // contrôle des périphériques

void taillefen(int *colonnes, int *lignes) // fonction qui récupère les dimmensions de la fenêtre
{
	struct winsize fen;	//structure de la librairie ioctl.h contenant des informations sur la fenêtre
	int col; // variable qui contiendra le nombre de colonnes
	int lig; // variable qui contiendra le nombre de lignes

	ioctl(0, TIOCGWINSZ, &fen); // instruction de ioctl permettant de connaître la taille de la fenêtre

	col = fen.ws_col;
	lig = fen.ws_row;

	*colonnes = col;
	*lignes = lig;
}

int main()
{
	FILE *f;		//création du pointeur vers le fichier
	char ligne[500];	// création de la chaine de caractère qui stockera la ligne
	char type[10];	// création de la variable contenant le type de PBM
	char *tok = NULL; // création du token pour strtok
	int dim[2];	//création d'un tableau
	int *lignes = malloc(sizeof(int *)); // création du pointeur qui contiendra le nombre de lignes
	int *colonnes = malloc(sizeof(int *));	// création du pointeur qui contiendra le nombre de colonnes
	int n; // variable compteur (pour parcourir toute la ligne)
	int nc = 0;
	char derniereligne[500];
	int nbradd = 3;
	int i = 0;
	int w = 0;
	taillefen(colonnes, lignes); // on appelle la fonction pour connaître la taille de la fenêtre

	f = fopen("8.pbm", "r");	// on met l'adresse du fichier dans le pointeur

	for(n=0; n<2;)	//tant que n est inferieur a 2 (qu'on a pas trouvé 2 lignes sans commentaires)
	{
		fgets(ligne, 500, f); // on rentre la ligne actuelle dans "ligne"
		if(strncmp(ligne, "#", 1)) // on vérifie que le premier caractère n'est pas "#" (un commentaire), sinon on change de ligne
		{
				if(n) //si on est déjà passé une fois dans la boucle, on gère les dimmensions
				{
					tok = strtok(ligne, " ");	// on stocke la première dimmension (largeur) dans tok
					dim[0] = atoi(tok);	// conversion (atoi) du char en int puis stockage dans tab[0]
					tok = strtok(NULL, " "); // on stocke la deuxième dimmension (longueur) dans tok
					dim[1] = atoi(tok);	// conversion (atoi) du char en int puis stockage dans tab[1]
					n++; //incrémentation du compteur (passe a 2 donc on sort du for)
				}
				else // sinon, c'est qu'on y est jamais passé donc on gère le type
				{
					strcpy(type, ligne); // copie la chaine "ligne" dans "type" puisque à cette étape ligne = type
					type[strcspn(type, "\n")] = '\0'; // On supprime le retour à la ligne de la fin de ligne
					n++; //incrémentation du compteur (passe à 1) donc la prochaine ligne contiendra les dimmensions
				}
				
		}
	}
	n = 0; // on réinitialise le compteur pour la nouvelle boucle

		while(fgets(ligne, 100,f)!= NULL) // tant que la ligne existe
		{
			
			nc = 0;
			if(strncmp(ligne, "#", 1)) // on vérifie que le premier caractère n'est pas "#" (un commentaire), sinon on change de ligne
			{
				/**/if(n == 3 | n == nbradd+4) //si nous en sommes à la 3 ème ou 4+nbradd ème ligne du chiffre
				{
					if (nbradd > 1)  // si nous sommes à un format supérieur à 5 par 3
					{
						i = 0;
						for(i = 0; i < nbradd;) //tant que nous n'avon pas ajouté suffisemment de lignes 
						{
							printf("%s\n",derniereligne); //print la dernière ligne entrée
							i++;
							n++;
						}
						w = 1;
					}
				}
				if(w == 0)
				{/**/
					strcpy(derniereligne,""); //réinitialisation de derniereligne
					tok = strtok(ligne, " "); // découpage du premier morceau jusqu'au séparateur (" ") (permet la suppression des espace)
					while(tok != NULL)	// tant que le token n'est pas vide (tant qu'on a pas atteint la fin de la ligne)
					{
						if(!(strncmp(tok, "1", 1))) // si on lit 1 dans le .pbm
						{
							/**/if(nc == 2) //si on est au deuxieme caractere de la ligne
							{
								i = 0;
								for(i = 0; i < nbradd;) //tant que nous n'avons pas ajouté tout les █ nécessaires
								{
									printf("█");
									i++;
									strcat(derniereligne,"█"); //entrer █ dans la chaine derniereligne
									nc++; // on passe au caractère suivant
								}
							}/**/
							else
							{
								printf("█");	// on affiche le caractère █
								/**/strcat(derniereligne,"█"); //entrer █ dans la chaine derniereligne
								nc++;/**/  // on passe au caractère suivant
							}
						}
						else	// si on lit un 0 dans le .pbm
						{
							/**/if(nc == 2) //si on est au deuxieme caractere de la ligne
							{
								i = 0;
								for(i = 0; i < nbradd;) //tant que nous n'avons pas ajouté tout les   nécessaires
								{
									printf(" ");
									i++;
									strcat(derniereligne," "); //entrer   dans la chaine derniereligne
									nc++; // on passe au caractère suivant
								}
							}/**/
							else
							{
								printf(" ");	// sinon afficher un espace
								/**/strcat(derniereligne," "); //entrer   dans la chaine derniereligne
								nc++;/**/  // on passe au caractère suivant
							}
						}
						tok = strtok(NULL, " "); // on passe au token suivant
					}
					printf("\n");	// retour à la ligne à la fin de chaque lignes
				/**/}/**/
			}
			n++;
		/**/}/**/
	printf("Le fichier PBM est de type %s\n", type);
	printf("Largeur = %d Longueur = %d.\n", dim[0], dim[1]);
	printf("Ce terminal possède %d colonnes et %d lignes.\n", *colonnes, *lignes);

	fclose(f); // fermeture du fichier .pbm
	free(lignes);
	free(colonnes);
	return 0;
}