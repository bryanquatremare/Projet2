#include <stdio.h> // traitement entrées/sortie
#include <string.h>
void lectureligne(char ligne[70])
{
	int n;
	for(n=0;n<strlen(ligne);n++)
	{
		if(ligne[n] == '1')
		{
			printf("%s","#");
		}
		else
		{
			printf(" ");
		}
	}
}
int main()
{
	FILE* f, g, h, k, l, m;
	char type[10];
	char *tok = NULL;
	int tab[2];
	char ligne[70];

	f = fopen("test_coeur.pbm", "r");
	g = fopen("test_coeur.pbm", "r");
	h = fopen("test_coeur.pbm", "r");
	k = fopen("test_coeur.pbm", "r");
	l = fopen("test_coeur.pbm", "r");
	m = fopen("test_coeur.pbm", "r");
	
	fgets(type, 10, f);
	type[strcspn(type, "\n")] = '\0';
	fgets(ligne, 15, f);
	
	tok = strtok(ligne, " ");
	tab[0] = atoi(tok);
	tok = strtok(NULL, " ");
	tab[1] = atoi(tok);
	
	fgets(type, 10, g);
	fgets(ligne, 15, g);
	fgets(type, 10, h);
	fgets(ligne, 15, h);
	fgets(type, 10, k);
	fgets(ligne, 15, k);
	fgets(type, 10, l);
	fgets(ligne, 15, l);
	fgets(type, 10, m);
	fgets(ligne, 15, m);

	while(fgets(ligne, 70, f) != NULL)
	{
		lectureligne(f,ligne);
		lectureligne(g,ligne);
		lectureligne(h,ligne);
		lectureligne(k,ligne);
		lectureligne(l,ligne);
		lectureligne(m,ligne);
		printf("\n");
	}
	
	printf("Le fichier est PBM de type %s\n", type);
	printf("Largeur = %d Longeur = %d.\n", tab[0], tab[1]);

	fclose(f);
	fclose(g);
	fclose(h);
	fclose(k);
	fclose(l);
	fclose(m);

	return 0;
}
