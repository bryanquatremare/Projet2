#include <stdio.h> // traitement entrées/sortie
#include <string.h> // traitement des chaines de caractère
#include <sys/ioctl.h> // contrôle des périphériques

void taillefen(int *colonnes, int *lignes) // fonction qui récupère les dimmensions de la fenêtre
{
	struct winsize fen;
	int col;
	int lig;

	ioctl(0, TIOCGWINSZ, &fen);

	col = fen.ws_col;
	lig = fen.ws_row;

	*colonnes = col;
	*lignes = lig;
}