#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header.h"

void assemblage(char *ligne, char *num0, char *num1, char *num2, char *num3, char *num4, char *num5, char *num6, char *num7, char *num8, char *num9, char *sep, char *space)
{
	int *heuredizaine = malloc(sizeof(int *));
	int *minutedizaine = malloc(sizeof(int *));
	int *secondedizaine = malloc(sizeof(int *));
	int *heureunite = malloc(sizeof(int *));
	int *minuteunite = malloc(sizeof(int *));
	int *secondeunite = malloc(sizeof(int *));
	int n = 0;
	int m = 0;
	int o = 0;
	int p = 0;
	int i = 0;
	char *numeroun = num1;
	char *numerodeux = num2;
	char *numerotrois = num3;
	char *numeroquatre = num4;
	char *numerocinq = num5;
	char *numerosix = num6;
	char *numerosept = num7;
	char *numerohuit = num8;
	char *numeroneuf = num9;
	char *numerozero = num0;

	char un[30], deux[30], trois[30], quatre[30], cinq[30], six[30];

	heurelocale(heuredizaine, heureunite, minutedizaine, minuteunite, secondedizaine, secondeunite);

	switch(*heuredizaine)
	{
		case 1:
		strcpy(un, numeroun);
		break;

		case 2:	
		strcpy(un, numerodeux);
		break;

		default:
		strcpy(un, numerozero);
		break;
	}
	

	switch(*heureunite)
	{
		case 1:
		strcpy(deux, numeroun);
		break;

		case 2:
		strcpy(deux, numerodeux);
		break;

		case 3:
		strcpy(deux, numerotrois);
		break;

		case 4:
		strcpy(deux, numeroquatre);
		break;

		case 5:
		strcpy(deux, numerocinq);
		break;

		case 6:
		strcpy(deux, numerosix);
		break;

		case 7:
		strcpy(deux, numerosept);
		break;

		case 8:
		strcpy(deux, numerohuit);
		break;

		case 9:
		strcpy(deux, numeroneuf);
		break;

		default:
		strcpy(deux, numerozero);
		break;
	}

	switch(*minutedizaine)
	{
		case 1:
		strcpy(trois, numeroun);
		break;

		case 2:
		strcpy(trois, numerodeux);
		break;

		case 3:
		strcpy(trois, numerotrois);
		break;

		case 4:
		strcpy(trois, numeroquatre);
		break;

		case 5:
		strcpy(trois, numerocinq);
		break;

		default:
		strcpy(trois, numerozero);
		break;
	}

	switch(*minuteunite)
	{
		case 1:
		strcpy(quatre, numeroun);
		break;

		case 2:
		strcpy(quatre, numerodeux);
		break;

		case 3:
		strcpy(quatre, numerotrois);
		break;

		case 4:
		strcpy(quatre, numeroquatre);
		break;

		case 5:
		strcpy(quatre, numerocinq);
		break;

		case 6:
		strcpy(quatre, numerosix);
		break;

		case 7:
		strcpy(quatre, numerosept);
		break;

		case 8:
		strcpy(quatre, numerohuit);
		break;
;
		case 9:
		strcpy(quatre, numeroneuf);
		break;

		default:
		strcpy(quatre, numerozero);
		break;
	}

	switch(*secondedizaine)
	{
		case 1:
		strcpy(cinq, numeroun);
		break;

		case 2:
		strcpy(cinq, numerodeux);
		break;

		case 3:
		strcpy(cinq, numerotrois);
		break;

		case 4:
		strcpy(cinq, numeroquatre);
		break;

		case 5:
		strcpy(cinq,  numerocinq);
		break;

		default:
		strcpy(cinq, numerozero);
		break;
	}

	switch(*secondeunite)
	{
		case 1:
		strcpy(six, numeroun);
		break;

		case 2:
		strcpy(six, numerodeux);
		break;

		case 3:
		strcpy(six, numerotrois);
		break;

		case 4:
		strcpy(six, numeroquatre);
		break;

		case 5:
		strcpy(six, numerocinq);
		break;

		case 6:
		strcpy(six, numerosix);
		break;

		case 7:
		strcpy(six, numerosept);
		break;

		case 8:
		strcpy(six, numerohuit);
		break;

		case 9:
		strcpy(six, numeroneuf);
		break;

		default:
		strcpy(six, numerozero);
		break;
	}
	printf("avant le while");
	while(n < 6 )
	{
		printf("Avant le for");
		for(i = 0; i < 12;)
		{
			printf("avant la lecture de la ligne du premier nombre");
			m = o;
			p = o;
			while(un[m] != 2)
				{
					printf("%c", un[m]);
					printf("%d", m);
					sprintf(ligne,"%c", un[m]);
					m++;
					o++;
				}
			m = p;
			while(space[m] != 2)
				{
					sprintf(ligne,"%c", space[m]);
					m++;
				}
			m = p;
			while(deux[m] != 2)
				{
					sprintf(ligne,"%c", deux[m]);
					m++;
				}
			m = p;
			while(sep[m] != 2)
				{
					sprintf(ligne,"%c", sep[m]);
					m++;
				}
			m = p;
			while(trois[m] != 2)
				{
					sprintf(ligne,"%c", trois[m]);
					m++;
				}
			m = p;
			while(space[m] != 2)
				{
					sprintf(ligne,"%c", space[m]);
					m++;
				}
			m = p;
			while(quatre[m] != 2)
				{
					sprintf(ligne,"%c", quatre[m]);
					m++;
				}
			m = p;
			while(sep[m] != 2)
				{
					sprintf(ligne,"%c", sep[m]);
					m++;
				}
			m = p;
			while(cinq[m] != 2)
				{
					sprintf(ligne,"%c", cinq[m]);
					m++;
				}
			m = p;
			while(space[m] != 2)
				{
					sprintf(ligne,"%c", space[m]);
					m++;
				}
			m = p;
			while(six[m] != 2)
				{
					sprintf(ligne,"%c", six[m]);
					m++;
				}
		}
		sprintf(ligne,"%c", '2');
		n++;
		printf("après l'ecriture de toute une ligne");
	}
	printf("après l'ecriture de tout ce qu'il ya a ecrire");
	free(heuredizaine);
	free(heureunite);
	free(minutedizaine);
	free(minuteunite);
	free(secondedizaine);
	free(secondeunite);
}