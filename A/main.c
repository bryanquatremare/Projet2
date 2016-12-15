#include <stdio.h>//Input/Output
#include <stdlib.h>//Malloc, ...
#include <string.h>//String manipulation
#include <sys/ioctl.h>//Get term size
#include <unistd.h>

#include "static.h"
#include "PBM.h"

int main(int argc, char *argv[])
{
//Load terminal size
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	int col = w.ws_col;
	int row = w.ws_row;

//Init some vars
	char **table = NULL;
	char *image = NULL;
	image = malloc(sizeof(char) * col * (row+4));

	int size[2];
	int i, j;
	char path[256];
	char type[256];

	if(getenv("EXIASAVER1_PBM") != NULL) //If EXIASAVER1_PBM exist, we put its content in the path
	{
		strcpy(path, getenv("EXIASAVER1_PBM"));
	}
	else
	{
		strcpy(path, ".");
	}
	strcat(path, "/");
	strcat(path, argv[1]); //On finit d'ecrire le chemin

	readPBM(path, size, type, image);

	//Allocate memory to the table

	table = malloc(sizeof(char *) * col * row);

	if(table == NULL)//Print error if allocation failed
	{
		printf("Error allocating memory");
		exit(EXIT_FAILURE);
	}

	for(i=0; i<row; i++)
	{
		table[i] = malloc(col * row * sizeof(char));
		if(table[i] == NULL)//Print error if allocation failed
		{
			printf("Error allocating memory");
			exit(EXIT_FAILURE);
		}
	}

	for(i=0; i<row; i++)//Initialize all the table to space
	{
		for(j=0; j<col; j++)
		{
	 		table[i][j] = ' ';
	 	}
	}

	strToTable(table, image, col, row, size);
	printf("'%s'", image);
	printTable(table, col, row);
	getch();
	system("clear");
	
	free(image);
	free(table);
	return 0;	
}