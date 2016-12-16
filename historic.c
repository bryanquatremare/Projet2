#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

void writeHisto(int type, char *arg)
{
	char annees[10];
	char mois[10];
	char jours[10];
	char heures[10];
	char minutes[10];
	char secondes[10];
	FILE *log;

	time_t timer; // création de timer avec un paramètre spécial time_t afin qu'il puisse stocker toute la date
	struct tm * t; // création de t qui pourra contenir la date sous la forme d'une structure
	time(&timer); //réception de la date dans timer
	t = localtime(&timer); // réception de la date contenue dans timer dans la structure t
	
	sprintf(annees,"%04u",t->tm_year+1900);
	sprintf(mois,"%02u",t->tm_mon);
	sprintf(jours,"%02u",t->tm_mday);
	sprintf(heures,"%02u",t->tm_hour);
	sprintf(minutes,"%02u",t->tm_min);
	sprintf(secondes,"%02u",t->tm_sec);

	log = fopen("historique", "a+");

	fprintf(log, "%s/%s/%s;%s:%s:%s;%d;%s\n", jours, mois, annees, heures, minutes, secondes, type, arg);
	fclose(log);
}

int typeLine(char **table, int i)//Get the type of the i line of the file
{
	char *tok;
	char tmp[1024];
	int result;

	strcpy(tmp, table[i]);
	tok = strtok(tmp, ";");
	tok = strtok(NULL, ";");
	tok = strtok(NULL, ";");

	result = atoi(tok);
	return result;
}

int lineNumber()//Get the number of line of the historic
{
	int i = 0;
	char tmp[1024];
	FILE *f;

	if(!(f = fopen("historique", "r")))
	{
		printf("Erreur durant la lecture de l'historique");
		exit(1);
	}

	while(fgets(tmp, 1024, f) != NULL) 
		i++;

	fclose(f);

	return i;

}

int num(char *str)//Transform the date in a timestamp
{
	char date[16];
	char hours[16];
	char *tok = NULL;
	int time;

	struct tm tm;

	tok = strtok(str, ";");
	strcpy(date, tok);
	tok = strtok(NULL, ";");
	strcpy(hours, tok);

	tm.tm_mday = atoi(strtok(date, "/"));
	tm.tm_mon = atoi(strtok(NULL, "/"));
	tm.tm_year = atoi(strtok(NULL, "/"));
	tm.tm_hour = atoi(strtok(hours, ":"));
	tm.tm_min = atoi(strtok(NULL, ":"));
	tm.tm_sec = atoi(strtok(NULL, ":"));;
	tm.tm_wday = 0;
	tm.tm_yday = 0;
	tm.tm_isdst = 0;

	time = mktime(&tm);

	return time;
}

void triDate(char **table)//Sort by increasing dates
{
	int i, a, b, redo = 1;
	char tmp[64];

	while(redo)
	{
		redo = 0;
		for(i=0; i<lineNumber()-1; i++)
		{
			strcpy(tmp, table[i]);
			a = num(tmp);
			strcpy(tmp, table[i+1]);
			b = num(tmp);

			if(a>b)
			{
				strcpy(tmp, table[i+1]);
				strcpy(table[i+1], table[i]);
				strcpy(table[i], tmp);
				redo = 1;
			}
		}
	}
}

void reverseTriDate(char **table)//Sort by decreasing dates
{
	int i, a, b, redo = 1;
	char tmp[64];

	while(redo)
	{
		redo = 0;
		for(i=lineNumber()-1; i>0; i--)
		{
			strcpy(tmp, table[i]);
			a = num(tmp);
			strcpy(tmp, table[i-1]);
			b = num(tmp);

			if(a>b)
			{
				strcpy(tmp, table[i-1]);
				strcpy(table[i-1], table[i]);
				strcpy(table[i], tmp);
				redo = 1;
			}
		}
	}
}

void triType(char **table)//Sort by type
{
	int i, a, b, redo = 1;
	char tmp[64];

	while(redo)
	{
		redo = 0;
		for(i=0; i<lineNumber()-1; i++)
		{
			a = typeLine(table, i);
			b = typeLine(table, i+1);

			if(a>b)
			{
				strcpy(tmp, table[i+1]);
				strcpy(table[i+1], table[i]);
				strcpy(table[i], tmp);
				redo = 1;
			}
		}
	}
}

char **histoToTable(char **table)//Put the historique file in a 2D table
{
	FILE *f;
	
	char tmp[64];
	int i;
	int nbLigne = lineNumber();

	table = malloc(nbLigne * sizeof(char *));
	for(i=0; i<nbLigne; i++)
		table[i] = malloc(64 * sizeof(char));

	if(!(f = fopen("historique", "r")))
	{
		printf("Erreur durant la lecture de l'historique");
		exit(1);
	}

	i = 0;
	while(fgets(tmp, 64, f) != NULL)
	{
		strcpy(table[i], tmp);
		i++;
	}

	fclose(f);
	return table;
}

void printHisto(char **table) //Print the historic
{
	int i;

	for(i=0; i<lineNumber(); i++)
		printf("%s", table[i]);
}