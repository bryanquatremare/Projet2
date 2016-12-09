#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <math.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <termios.h>

char *readPBM(char *path, int *size, char *output)//Input : path, size[2], output
{
	//Define the vars
	FILE *f;

	char *image = NULL;
	char *tok = NULL;
  	char tmp[1024];
  	char line[500];
	char type[500];

	int fd[2];
  	int i, j, n;
  	int temp;

  	//Open the pipe for inter-process communication
  	pipe(&fd[0]);

  	//Fork and test if we are child or parent process
	if(fork()!=0) //Parent process
	{
		wait(NULL); //Wait for child's end
		close(fd[1]);//Close pipe's write stream
		close(0);//Close stdin
		dup(fd[0]);//Duplicate stdout
		close(fd[0]);//Close old stdout
		

		fgets(type, 500, stdin); //Put first entry in type
		fgets(tmp, 1024, stdin); //Second in tmp then convert in int
		size[0] = atoi(tmp); 
		fgets(tmp, 1024, stdin); //Same for third
		size[1] = atoi(tmp);

		strcpy(output, "");//Empty output
		i = 0;
		j = 0;
  		while(fgets(tmp, 1024, stdin) != NULL) //Put remainings entry in output
  		{
			strcat(output, tmp);
  		}
	}
	else //Child process
	{
  		close(fd[0]);//Close pipe's read stream
		close(1);//Close stdout
		dup(fd[1]);//Duplicate stdin
		close(fd[1]);//Close old stdin


		f = fopen(path, "r");

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

		fclose(f);
	}
	return output;
}

int **initTable(int **table, int size[])//Input : **table, size[2]
{
	int i, j;

	//Allocate memory to the table

	table = malloc(sizeof(int *) * size[0] * size[1]);

	for(i=0; i<size[1]; i++)
	{
		table[i] = malloc(size[1] * size[0] * sizeof(int));
	}

	for(i=0; i<size[0]; i++)//Initialize all the table to 0
	{
		for(j=0; j<size[1]; j++)
		{
	 		table[j][i] = 0;
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
			printf("#");
			table[i][j] = 1;
		}
		else if(str[n] == '2')//Go to next row in the table
		{
			printf("\n");
			j++;
		}
		else//Let the 0 in the table
		{
			printf(" ");
		}
		i++;
	}
}

int main(int argc, char *argv[])
{
	char *str = malloc(4096 * sizeof(char)); //Allocate memory

	//Define the vars
	int **table = NULL;
	int size[2];
	int i, j;

	readPBM("./heart.pbm", size, str); //Read the picture file
	table = initTable(table, size); //Initialize the table
	strToTable(table, str, size); //Transform the string to a table
	for(i=0; i<size[0]; i++) //Print the whole table
	{
		for(j=0; j<size[1]; j++)
		{
	 		printf("%d", table[i][j]);
	 	}
	 	printf("\n");
	}
	free(str); //Free memory
	free(table);
}