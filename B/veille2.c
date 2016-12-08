#include <stdlib.h>
#include <stdio.h>
#include <time.h> //ajout librairie pour utiliser les fontions manipulatrices de dates locales et systèmes

void main()
{
	time_t timer; // création de timer avec un paramètre spécial time_t afin qu'il puisse stocker toute la date
	struct tm * t; // création de t qui pourra contenir la date sous la forme d'une structure

	time(&timer); //récéption de la date dans timer


	t = localtime(&timer); // réception de la date contenue dans timer dans la structure t
	printf("%02uh %02um %02us\n", t->tm_hour, t->tm_min, t->tm_sec); // affichage de l'heure les minutes et les secondes avec l'appel %02u
}
