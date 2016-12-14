#include <stdio.h> // traitement entrées/sortie
#include <string.h> // traitement des chaines de caractère
#include <sys/ioctl.h> // contrôle des périphériques

void taillefen(int *colonnes, int *lignes) // fonction qui récupère les dimmensions de la fenêtre
{
	struct winsize fen; // structure dans la bibliothèque sys/ioctl.h
	int col; // initialisation de la variable contenant le nombre de colonnes
	int lig; // initialisation de la variable contenant le nombre de lignes

	ioctl(0, TIOCGWINSZ, &fen);

	col = fen.ws_col; // on rentre la valeur de la sous-variable de la structure winsize 
	lig = fen.ws_row;

	*colonnes = col;
	*lignes = lig;
}