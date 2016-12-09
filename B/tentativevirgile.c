#include <stdio.h> // traitement entrées/sortie
#include <string.h>
void lectureligne(FILE *pointeur,char ligne[100])
{
	int n;
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

	f = fopen("1.pbm", "r");
	g = fopen("2.pbm", "r");
	h = fopen("5.pbm", "r");
	k = fopen("9.pbm", "r");
	l = fopen("3.pbm", "r");
	m = fopen("7.pbm", "r");

	while(fgets(ligne, 100, f) != NULL)
	{
		lectureligne(f,ligne);
		lectureligne(g,ligne);
		lectureligne(h,ligne);
		lectureligne(k,ligne);
		lectureligne(l,ligne);
		lectureligne(m,ligne);
		printf("\n");
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
