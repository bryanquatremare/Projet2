#include <stdlib.h> // routines standards
#include <stdio.h> // traitement entrées/sortie
#include <string.h> // tratement de chaine de caractères
#include <time.h>
#include <unistd.h>
#include <termios.h>

#include "historic.h"

int rand_screen();
char getch();

int main(int argc, char *argv[])
{
	int stat = 1;
	if(argc > 1)
		if(strcmp(argv[1], "-stats")  == 0) stat = 0;
	if(stat)//If we do not want to print the stats
	{
		int num;
		int img;
		char *param[256];
		char pbm[256];
		char home[30];
		char coord[10];
		char pause[10];
		system("clear");
		srand(time(NULL));
		num = rand_screen(1, 3);

		if(!(getenv("EXIASAVER_HOME") == NULL))
		{
			strcpy(home, getenv("EXIASAVER_HOME"));
		}
		else
		{
			strcpy(home, ".");
		}

		switch(num)
		{
			case 1:
			strcat(home, "/A");
			img = rand_screen(1, 5);
			sprintf(pbm, "A%d.pbm", img);
			param[0] = "A";
			param[1] = pbm;
			param[2] = NULL;
			writeHisto(1, param[1]);
			execv(home, param);
			break;

			case 2:
			strcat(home, "/B");
			param[0] = "B";
			param[2] = NULL;
			writeHisto(2, "");
			execv(home, NULL) ;
			break;

			case 3:
			strcat(home, "/C");
			strcpy(coord, "");
			sprintf(coord, "%dx%d", rand_screen(0, 80), rand_screen(0, 24));
			param[0] = "C";
			param[1] = coord;
			param[2] = NULL;
			writeHisto(3, coord);
			execv(home, param);
			break;
		}
	    return 0;
	}
	else//We want to print the stats
	{
		int c, i, redo = 1;
		int nbLigne = lineNumber();
		char **table = NULL;
		char d;

		table = histoToTable(table);

		system("clear");
		while(redo)
		{
			redo = 0;
			printf("Veuillez choisir comment trier les stats :\n 1 - Tri par date croissante\n 2 - Tri par date décroissante\n 3 - Tri par type\n");
			d = getch();

			switch (d)
			{
				case '1':
					triDate(table);
					break;
				case '2':
					reverseTriDate(table);
					break;
				case '3':
					triType(table);
					break;
				default :
					system("clear");
					printf("Veuillez faire un choix valide.\n");
					redo = 1;
			}
		}
		system("clear");
		printHisto(table);
		printf("\nNombre de lancer de l'eXiaSaver : %d\n", lineNumber());

		for(i=0; i<nbLigne; i++)
			free(table[i]);

		free(table);
		return 0;

	}
}

int rand_screen(int a, int b)
{
	b++;
	return rand()%(b-a) +a;
}

char getch()
{
	char ch;
	struct termios old, new;
	tcgetattr(0, &old); // grab old terminal i/o settings
	new = old; // new settings = old settings
	new.c_lflag &= ~ICANON; // disable buffered i/o
	new.c_lflag &= ~ECHO; //set echo mode
	tcsetattr(0, TCSANOW, &new); // use these new terminal i/o settings now
	ch = getchar();
	tcsetattr(0, TCSANOW, &old); //restore old settings
	return ch;
}