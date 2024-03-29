#include <stdio.h>//Input/output 
#include <stdlib.h>//Memory allocation, convert char to int, ...
#include <string.h>//String manipulation
#include <unistd.h>//Fork, pipe
#include <sys/wait.h>//Wait function

#define CHAR_PRINTED "#"

/* We use a code to read and process the PBM :
0 = space
1 = #
2 = \n
*/

void readPBM(char *path, int *size, char *type, char *output)
{
	FILE *f;

	char *tok = NULL;
  	char line[500];
	
  	int i;

	if(!(f = fopen(path, "r")))
	{
		printf("Error while reading the file");
		exit(EXIT_FAILURE);
	}

	for(i=0; i<2;)	
	{
		fgets(line, 500, f);
		if(strncmp(line, "#", 1))//If line start with #, line is a comment so we ignore it
		{
			if(i) //If we already made one iteration, get the size of the picture
			{
				tok = strtok(line, " ");
				size[0] = atoi(tok);
				tok = strtok(NULL, " ");
				size[1] = atoi(tok);
				i++;
			}
			else//Else get the type of the picture
			{
				strcpy(type, line);
				type[strcspn(type, "\n")] = '\0';
				i++;
			}
			
		}
	}
	while(fgets(line, 100, f) != NULL)
	{
		tok = strtok(line, " ");
		while(tok != NULL)//Print the lines of the pictures to the parent process while ignoring spaces
		{
			if(!(strncmp(tok, "1", 1)))
			{
				strcat(output, "1");
			}
			else
			{
				strcat(output, "0");
			}
			tok = strtok(NULL, " ");
		}
		strcat(output, "2");//Print 2 as an "End of line" character
	}
	printf("\n");
	fclose(f);
	
}
















int **initTable(int **table, int *size)//Input : **table, size[2]
{
	int i, j;

	//Allocate memory to the table

	table = malloc(sizeof(int *) * size[0] * size[1]);

	if(table == NULL)//Print error if allocation failed
	{
		printf("Error allocating memory");
		exit(EXIT_FAILURE);
	}

	for(i=0; i<size[0]; i++)
	{
		table[i] = malloc(size[1] * size[0] * sizeof(int));
		if(table[i] == NULL)//Print error if allocation failed
		{
			printf("Error allocating memory");
			exit(EXIT_FAILURE);
		}
	}

	for(i=0; i<size[0]; i++)//Initialize all the table to 0
	{
		for(j=0; j<size[1]; j++)
		{
	 		table[i][j] = 0;
	 	}
	}
	return table;
}

void strToTable(int **table, char *str, int size[])//Input : table[][], str, size[2]
{
	int i, j, n;

	i = 0;
	j = 0;

	for(n=0;n<strlen(str);n++)
	{
		if(str[n] == '1')//Put '1' in the table when there is '1' in the string
		{
			table[i][j] = 1;
		}
		else if(str[n] == '2')//Go to next row in the table
		{
			j++;
			i = -1;
		}
		i++;
	}
}

void printTable(int **table, int size[])
{
	int i, j;
	for(i=0; i<size[1]; i++) //Print the whole table
	{
		for(j=0; j<size[0]; j++)
		{
			if(table[j][i] == 1)
	 		{
	 			printf(CHAR_PRINTED);
	 		}
	 		else
	 		{
	 			printf(" ");
	 		}
	 	}
	 	printf("\n");
	}
}