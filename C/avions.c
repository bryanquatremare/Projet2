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

void changeAvion(int tableau[][], int sens, avion avion)
{
	int i, j;
	//ignorer 2 premiere lignes + #
	if(sens == 0)//Vers le haut
	{
		for(i=0; i<6; i++)
		{
			for(j=0; j<6; j++)
			{
				tableau[avion.x+i][avion.y+j];
			}
		}
	}
}

int main(int argc, char *argv[])
{
	struct winsize w;

	avion avion;

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
	changeAvion(tableau, 0, avion);
	for(i=0; i<row; i++)
	{
		for(j=0; j<col; j++)
		{
	 		printf("%s", tableau[i][j]);
	 	}
	}

	for(i=0; i<row; i++)
	{
		free(tableau[i]);
	}
	free(tableau);
}