#include <stdlib.h>
#include <stdio.h> // traitement entrées/sortie
#include <string.h>
#include <time.h> //ajout librairie pour utiliser les fontions manipulatrices de dates locales et systèmes

void quelheure()
{
	time_t timer; // création de timer avec un paramètre spécial time_t afin qu'il puisse stocker toute la date
	struct tm * t; // création de t qui pourra contenir la date sous la forme d'une structure

	time(&timer); //réception de la date dans timer


	t = localtime(&timer); // réception de la date contenue dans timer dans la structure t
	printf("%02uh %02um %02us\n", t->tm_hour, t->tm_min, t->tm_sec); // affichage de l'heure les minutes et les secondes avec l'appel %02u
	char *heure = t->tm_hour;
	char *minute = t->tm_min;
	char *seconde = t->tm_sec;
}

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
	FILE *f, *g, *h, *k, *l, *m;
	int *heure = NULL, *minute = NULL, *seconde = NULL;
	char type[10];
	char *tok = NULL;
	int tab[2];
	char ligne[70];
	
	quelheure;
	printf("%s %s %s", *heure, *minute, *seconde);

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
		lectureligne(ligne);
		fgets(ligne, 70, g);
		lectureligne(ligne);
		fgets(ligne, 70, h);
		lectureligne(ligne);
		fgets(ligne, 70, k);
		lectureligne(ligne);
		fgets(ligne, 70, l);
		lectureligne(ligne);
		fgets(ligne, 70, m);
		lectureligne(ligne);
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
