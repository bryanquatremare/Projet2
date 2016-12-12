#include <stdio.h> // traitement entrées/sortie
#include <string.h> // traitement des chaines de caractère
#include <sys/ioctl.h> // contrôle des périphériques

void fentaille (int *colone, int *ligne) // fonction qui récupère les dimmensions de la fenêtre
{
	struct winsize fen;

	ioctl(0, TIOCGWINSZ, &fen)

	*colone = fen.ws_col;
	*ligne = fen.ws_row;
}