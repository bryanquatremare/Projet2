#include <stdio.h>//Input/output 
#include <stdlib.h>//Memory allocation, convert char to int, ...
#include <string.h>//String manipulation
#include <unistd.h>//Fork, pipe
#include <sys/wait.h>//Wait function

/* We use a code to read and process the PBM :
0 = space
1 = #
2 = \n
*/

void readPBM(char *path, int *size, char *type, char *output)
{
	FILE *f, *fp;

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

		fp = fdopen(fd[0], "r");

		fgets(type, 500, fp); //Put first entry in type
		type[strcspn(type, "\n")] = '\0';
		fgets(tmp, 1024, fp); //Second in tmp then convert in int
		size[0] = atoi(tmp); 
		fgets(tmp, 1024, fp); //Same for third
		size[1] = atoi(tmp);

		i = 0;
		strcpy(output, "");// Init output at 0
  		while(fgets(tmp, 1024, fp) != NULL) //Put remainings entry in output
  		{
			strcat(output, tmp);
  		}
  		output = strtok(output, "\n");
  		fclose(fp);
	}
	else if(pid == 0) //Child process
	{
  		close(fd[0]);//Close pipe's read stream
		close(1);//Close stdout
		dup(fd[1]);//Duplicate stdin
		close(fd[1]);


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
		exit(1);
	}
	else //Print error if fork failed
	{
		printf("Error creating a new process");
		exit(EXIT_FAILURE);
	}
}