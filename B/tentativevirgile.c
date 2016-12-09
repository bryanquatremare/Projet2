#include <stdio.h> // traitement entrées/sortie
#include <string.h>
void lectureligne(pointeur, ligne)
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
}

int main()
{
	FILE *f;
	FILE *g;
	FILE *h;
	FILE *k;
	FILE *l;
	FILE *m;
	
	char ligne[100];

	f = fopen("test_coeur.pbm", "r");
	g = fopen("test_coeur.pbm", "r");
	h = fopen("test_coeur.pbm", "r");
	k = fopen("test_coeur.pbm", "r");
	l = fopen("test_coeur.pbm", "r");
	m = fopen("test_coeur.pbm", "r");
	int n;
	while(fgets(ligne, 100, f) != NULL)
	{
		lectureligne(f,ligne);
		lectureligne(g,ligne);
		lectureligne(h,ligne);
		lectureligne(k,ligne);
		lectureligne(l,ligne);
		lectureligne(m,ligne);
		print("\n");
	}
	fclose(f);
	fclose(g);
	fclose(h);
	fclose(k);
	fclose(l);
	fclose(m);
	
	return 0;
}

// mettre 2 if cote a cote pour les 2 chiffres