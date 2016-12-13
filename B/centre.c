#include <stdio.h>

void centre(int *axelig, int *axecol, int axepbm) // fonction pour centrer l'image
{
int n = 1; // compteur de saut de ligne
	if(*axecol >= 100 & *axelig >=35)
	{
		while(n != (*axelig/2)-(axepbm)) // tant que la ligne actuelle (n) n'est pas égale au centre
		{	
			printf("\n"); // sauter une ligne
			n++; // ajouter 1 à la ligne actuelle
		}

		if((*axelig/2)-(axepbm) % 2 != 0) // si le nombre total de sauts de lignes est impair
		{
			printf("\n"); // rajouter un saut de ligne
		}
	}
	else
	{
		while(n != (*axelig/2)-(axepbm/2)) // tant que la ligne actuelle (n) n'est pas égale au centre
		{	
			printf("\n"); // sauter une ligne
			n++; // ajouter 1 à la ligne actuelle
		}

		if((*axelig/2)-(axepbm/2) % 2 != 0) // si le nombre total de sauts de lignes est impair
		{
			printf("\n"); // rajouter un saut de ligne
		}
	}
}