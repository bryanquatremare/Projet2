#include <stdlib.h>
#include <stdio.h> // traitement entrées/sortie
#include <string.h>
#include <time.h> //ajout librairie pour utiliser les fontions manipulatrices de dates locales et systèmes
#include <math.h> // pour le header pour l'instant

void heurelocale(int *heuredizaine, int *heureunite, int *minutedizaine, int *minuteunite, int *secondedizaine, int *secondeunite)
{
	char h[2];
	char m[2];
	char s[2];
	int chiffretampon;
	time_t timer; // création de timer avec un paramètre spécial time_t afin qu'il puisse stocker toute la date
	struct tm * t; // création de t qui pourra contenir la date sous la forme d'une structure

	time(&timer); //réception de la date dans timer

	t = localtime(&timer); // réception de la date contenue dans timer dans la structure t
	sprintf(h,"%02u",t->tm_hour);
	sprintf(m,"%02u",t->tm_min);
	sprintf(s,"%02u",t->tm_sec);
	*heuredizaine = atoi(h);
	*minutedizaine = atoi(m);
	*secondedizaine = atoi(s);
	chiffretampon = floor(*heuredizaine / 10);
	*heureunite = *heuredizaine - chiffretampon * 10;
	*heuredizaine = chiffretampon;
	chiffretampon = floor(*minutedizaine / 10);
	*minuteunite = *minutedizaine - chiffretampon * 10;
	*minutedizaine = chiffretampon;
	chiffretampon = floor(*secondedizaine / 10);
	*secondeunite = *secondedizaine - chiffretampon * 10;
	*secondedizaine = chiffretampon;
	
	// dizaine = floor(*heure/10)
	//unité = *heure - dizaine*10
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
	int *heuredizaine = malloc(sizeof(int *));
	int *minutedizaine = malloc(sizeof(int *));
	int *secondedizaine = malloc(sizeof(int *));
	int *heureunite = malloc(sizeof(int *));
	int *minuteunite = malloc(sizeof(int *));
	int *secondeunite = malloc(sizeof(int *));
	
	char type[10];
	char *tok = NULL;
	int tab[2];
	char ligne[70];
	
	heurelocale(heuredizaine, heureunite, minutedizaine, minuteunite, secondedizaine, secondeunite);
	printf("%u%u %u%u %u%u", *heuredizaine, *heureunite, *minutedizaine, *minuteunite, *secondedizaine, *secondeunite);
	printf("\n");

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
	
	free(heuredizaine);
	free(heureunite);
	free(minutedizaine);
	free(minuteunite);
	free(secondedizaine);
	free(secondeunite);
	return 0;
}
