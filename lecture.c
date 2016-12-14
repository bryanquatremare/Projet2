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

void readPBM(char *path, int *size, char *type, char *output) // path = chemin du pbm, size = dim[], type = type[], output = ligne[]
{
	FILE *f;

	char *image = NULL;
	char *tok = NULL;
  	char tmp[1024];
  	char line[512];

	int fd[2];
  	int i, j, n, pid;

  	fflush(stdin);
  	fflush(stdout);

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
		

		fgets(type, 512, stdin); //Put first entry in type
		type[strcspn(type, "\n")] = '\0';
		fgets(tmp, 1024, stdin); //Second in tmp then convert in int
		size[0] = atoi(tmp); 
		fgets(tmp, 1024, stdin); //Same for third
		size[1] = atoi(tmp);

		i = 0;
		j = 0;
		strcpy(output, "");// Init output at 0
  		while(fgets(tmp, 1024, stdin) != NULL) //Put remainings entry in output
  		{
			strcat(output, tmp);
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
			fgets(line, 512, f);
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
		while(fgets(line, 512, f) != NULL)
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

// int main(int argc, char *argv[])
// {
// 	char *str = malloc(4096 * sizeof(char)); //Allocate memory
// 	if(str == NULL) //Print error if allocation failed
// 	{
// 		printf("Error allocating memory");
// 		exit(EXIT_FAILURE);
// 	}

// 	// //Define the vars
// 	char type[512];
// 	char path[256];

// 	int **table = NULL;
// 	int size[2];
// 	int i, j;

// 	strcpy(path, "coeur.pbm");

// 	if(argv[1] != NULL)
// 		strcpy(path, argv[1]);

// 	readPBM(path, size, type, str); //Read the picture file
// 	table = initTable(table, size); //Initialize the table
// 	strToTable(table, str, size); //Transform the string to a table
// 	printTable(table, size); //Print the table on screen

// 	free(str); //Free memory
// 	free(table);
// }