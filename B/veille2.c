#include <stdlib.h>
#include <stdio.h>
#include <time.h> //ajout librairie pour utiliser les fontions manipulatrices de dates locales et systèmes
#include <string.h>

void heurelocale(int *heure, int *minute, int *seconde)
{
	char h[2];
	char m[2];
	char s[2];
	time_t timer; // création de timer avec un paramètre spécial time_t afin qu'il puisse stocker toute la date
	struct tm * t; // création de t qui pourra contenir la date sous la forme d'une structure

	time(&timer); //récéption de la date dans timer

	t = localtime(&timer); // réception de la date contenue dans timer dans la structure t
	printf("%02uh %02um %02us\n", t->tm_hour, t->tm_min, t->tm_sec); // affichage de l'heure les minutes et les secondes avec l'appel %02u
	sprintf(h,"%02u",t->tm_hour);//récupération de l'heure dans le char "heure"
	sprintf(m,"%02u",t->tm_min);//récupération des minutes dans le char "minute"
	sprintf(s,"%02u",t->tm_sec);//récupération des secondes dans le char "seconde"
	printf("%s %s %s\n",h,m,s);
	*heure = h;
	*minute = m;
	*seconde = s;
}
