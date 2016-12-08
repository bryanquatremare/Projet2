#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>

typedef struct avion avion;
	struct avion
	{
    	int x;
    	int y;
    	int sens;
	};

void changeAvion(int **tableau, int sens, avion avion)
{
	FILE *fp;
	int i, j;
	char line[1024];
	char *p = NULL;
	char chemin[128];
	//ignorer 2 premiere lignes + #
	switch(sens)
	{
		case 0:
			strcpy(chemin, "avion_bas.pbm");
			break;
		case 1:
			strcpy(chemin, "avion_gauche.pbm");
			break;
		case 2:
			strcpy(chemin, "avion_haut.pbm");
			break;
		case 3:
			strcpy(chemin, "avion_droite.pbm");
			break;
	}	
	fp = fopen(chemin, "r");
	i = 0;
	while(i<2)
	{
		if(fgets(line,sizeof(line),fp)!= NULL) //Si la ligne n'est pas vide
		{
			if(strncmp(line, "#", 1) != 0) //On ignore les commentaires
			{
				i++;
			}
		}
	}
	i = 0;
	j = 0;
	while(fgets(line,sizeof(line),fp)!= NULL)
	{
		p = strtok(line, " ");
		while(p != NULL)
		{
			if(strncmp(p, "1", 1) == 0)
			{
				tableau[avion.x+j][avion.y+i] = 1;
			}
			p = strtok(NULL, " ");
			i++;
		}
		j++;
		i = 0;
	}
	fclose(fp);
	
}

int main(int argc, char *argv[])
{
	struct winsize w;

	avion avion;

	avion.x = 10;
	avion.y = 10;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int col = w.ws_col;
	int row = w.ws_row;
	int i;
	int j;
	int **tableau = malloc(col * row * sizeof(int*));

	for(i=0; i<row; i++)
	{
		tableau[i] = malloc(col * row * sizeof(int));
	}
	for(i=0; i<row; i++)
	{
		for(j=0; j<col; j++)
		{
	 		tableau[i][j] = 0;
	 	}
	}
	changeAvion(tableau, 2, avion);
	for(i=0; i<row; i++)
	{
		for(j=0; j<col; j++)
		{
	 		printf("%d", tableau[i][j]);
	 	}
	}

	for(i=0; i<row; i++)
	{
		free(tableau[i]);
	}
	free(tableau);
}