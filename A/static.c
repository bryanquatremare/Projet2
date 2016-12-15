#include <stdio.h>//Input/output 
#include <stdlib.h>//Memory allocation, convert char to int, ...
#include <string.h>//String manipulation
#include <termios.h>//Terminal I/O
#include <unistd.h>//STDIN_FILENO

char **initTable(char **table, int col, int row)//Input : **table, col, row
{
	int i, j;

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
	return table;
}

void strToTable(char **table, char *str, int col, int row, int *size)//Input : table[][], str, size[2]
{
	int i, j, n;

	i = (col - size[0]) / 2;
	j = (row - size[1]) / 2;

	for(n=0;n<strlen(str);n++)
	{
		if(str[n] == '1')//Put # in the table when there is '1' in the string
		{
			table[j][i] = '#';
		}
		else if(str[n] == '2')//Go to next row in the table
		{
			j++;
			i = (col - size[0]) / 2 - 1;
		}
		i++;
	}
}

void printTable(char **table, int col, int row)
{
	int i, j;
	for(i=0; i<row; i++) //Print the whole table
	{
		for(j=0; j<col; j++)
		{
			printf("%c", table[i][j]);
	 	}
	 	printf("\n");
	}
}

char getch()
{
	char ch;
	struct termios old, new;
	tcgetattr(0, &old); // grab old terminal i/o settings
	new = old; // new settings = old settings
	new.c_lflag &= ~ICANON; // disable buffered i/o (do not wait for \n)
	new.c_lflag &= ~ECHO; //disable echo mode
	tcsetattr(0, TCSANOW, &new); // use these new terminal i/o settings now
	ch = getchar();
	tcsetattr(0, TCSANOW, &old); //restore old settings
	return ch;
}