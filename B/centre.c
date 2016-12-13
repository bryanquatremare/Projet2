#include <stdio.h>

void centre(int *axeconsole, int axepbm) // fonction pour centrer l'image
{
int n = 1; // compteur de saut de ligne
while(n != (*axeconsole/2)-(axepbm/2)) // tant que la ligne actuelle (n) n'est pas égale au centre
	{	
		printf("\n"); // sauter une ligne
		n++; // ajouter 1 à la ligne actuelle
	}

	if((*axeconsole/2)-(axepbm/2) % 2 != 0) // si le nombre total de sauts de lignes est impair
	{
		printf("\n"); // rajouter un saut de ligne
	}
}