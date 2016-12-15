#include <stdio.h> // traitement entrées/sortie
#include <stdlib.h>
#include <string.h> // traitement des chaines de caractère
#include <stdio.h>//Input/output 
#include <stdlib.h>//Memory allocation, convert char to int, ...
#include <string.h>//String manipulation
#include <unistd.h>//Fork, pipe
#include <sys/wait.h>//Wait function

#define CHAR_PRINTED "#"

void readPBM(char *path, int *size, char *type, char *output)
{
	FILE *f;

	char *tok = NULL;
  	char tmp[1024]="";
  	char line[500]="";

	int fd[2] = {0,0};
  	int i, j, n, pid;

  	//Open the pipe for inter-process communication
  	pipe(&fd[0]);

  	//Fork and test if we are child or parent process
  	pid = fork();
	if(pid) //Parent process
	{
		wait(NULL); //Wait for child's end
		close(fd[1]);//Close pipe's write stream
		close(0);//Close stdin
		dup(fd[0]);//Duplicate stdout
		close(fd[0]);//Close old stdout
		

		fgets(type, 500, stdin); //Put first entry in type
		type[strcspn(type, "\n")] = '\0';
		fgets(tmp, 1024, stdin); //Second in tmp then convert in int
		size[0] = atoi(tmp); 
		fgets(tmp, 1024, stdin); //Same for third
		size[1] = atoi(tmp);

		i = 0;
		strcpy(output, "");// Init output at 0
  		while(i<8) //Put remainings entry in output
  		{
  			fgets(tmp, 1024, stdin);
			strcat(output, tmp);
			i++;
  		}
  		output = strtok(output, "\n");
	}
	else if(pid == 0) //Child process
	{
  		close(fd[0]);//Close pipe's read stream
		close(1);//Close stdout
		dup(fd[1]);//Duplicate stdin
		close(fd[1]);//Close old stdin


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
		//Print type and sizes to the parent process
		printf("%s\n", type);
		printf("%d\n", size[0]);
		printf("%d\n", size[1]);
		while(fgets(line, 100, f) != NULL)
		{
			tok = strtok(line, " ");
			while(tok != NULL)//Print the lines of the pictures to the parent process while ignoring spaces
    		{
				if(!(strncmp(tok, "1", 1)))
				{
					printf("1");
				}
				else
				{
					printf("0");
				}
				tok = strtok(NULL, " ");
			}
			printf("2");//Print 2 as an "End of line" character
		}
		printf("\n");
		fclose(f);
	}
	else //Print error if fork failed
	{
		printf("Error creating a new process");
		exit(EXIT_FAILURE);
	}
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

int main()
{
	int dimnum[200];
	char type[1000];

	char *num = malloc(2560 * sizeof(char));
	char *num1 = malloc(2560 * sizeof(char));
	char *num2 = malloc(2560 * sizeof(char));
	char *num3 = malloc(2560 * sizeof(char));
	char *num4 = malloc(2560 * sizeof(char));
	char *num5 = malloc(2560 * sizeof(char));
	char *num6 = malloc(2560 * sizeof(char));
	char *num7 = malloc(2560 * sizeof(char));
	char *num8 = malloc(2560 * sizeof(char));
	char *num9 = malloc(2560 * sizeof(char));
	char *sep = malloc(2560 * sizeof(char));

	readPBM("0.pbm", dimnum, type, num);
	printf("%s\n", num);
	readPBM("1.pbm", dimnum, type, num1);
	printf("%s\n", num1);
	readPBM("2.pbm", dimnum, type, num2);
	printf("%s\n", num2);
	readPBM("3.pbm", dimnum, type, num3);
	printf("%s\n", num3);
	readPBM("4.pbm", dimnum, type, num4);
	printf("%s\n", num4);
	readPBM("5.pbm", dimnum, type, num5);
	printf("%s\n", num5);
	readPBM("6.pbm", dimnum, type, num6);
	printf("%s\n", num6);
	readPBM("7.pbm", dimnum, type, num7);
	printf("%s\n", num7);
	readPBM("8.pbm", dimnum, type, num8);
	printf("%s\n", num8);
	readPBM("9.pbm", dimnum, type, num9);
	printf("%s\n", num9);
	readPBM("sep.pbm", dimnum, type, sep);
	printf("%s\n", sep);
	

	free(num);
	free(num1);
	free(num2);
	free(num3);
	free(num4);
	free(num5);
	free(num6);
	free(num7);
	free(num8);
	free(num9);
	free(sep);
}
