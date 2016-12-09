#include <stdio.h> // traitement entrées/sortie
#include <string.h>

int main()
{
	FILE *f;
	char ligne[100];
	int n;

	f = fopen("test_coeur.pbm", "r");

	while(fgets(ligne, 100, f) != NULL)
	{
		for(n=0;n<strlen(ligne);n++)
		{
			if(ligne[n] == '1')
			{
				printf("%c", 219);
			}
			else
			{
				printf(" ");
			}
		}
		printf("\n");
	}

	fclose(f);
	return 0;
}

// mettre 2 if cote a cote pour les 2 chiffres