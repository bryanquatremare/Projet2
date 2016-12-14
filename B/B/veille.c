#include <stdio.h> // traitement entrées/sortie
#include <stdlib.h>
#include <string.h> // traitement des chaines de caractère
#include <math.h>
#include <time.h>

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
/* voila un exemple d'appel à la fonction ci-dessus

int main()
{
	int *heuredizaine = malloc(sizeof(int *));
	int *minutedizaine = malloc(sizeof(int *));
	int *secondedizaine = malloc(sizeof(int *));
	int *heureunite = malloc(sizeof(int *));
	int *minuteunite = malloc(sizeof(int *));
	int *secondeunite = malloc(sizeof(int *));
	
	heurelocale(heuredizaine, heureunite, minutedizaine, minuteunite, secondedizaine, secondeunite);
	printf("%u%u %u%u %u%u", *heuredizaine, *heureunite, *minutedizaine, *minuteunite, *secondedizaine, *secondeunite);
}

*/