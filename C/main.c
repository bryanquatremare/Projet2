#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "avions.h"
#include "lecture.h"

#define CHAR_PRINTED "#"

typedef struct plane plane;
	struct plane
	{
    	int x;
    	int y;
    	int sens;
	};

int main(int argc, char *argv[])
{
//Load terminal size
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	int col = w.ws_col;
	int row = w.ws_row - 1;

//Init some var
	int i, j;
	char **table = malloc(col * row * sizeof(char*));
	char c = ' ';
	char type[256], path[256], *tmp = NULL;

//Init plane structure
	plane plane;

	if(argv[1] != NULL)
	{
		tmp = strtok(argv[1], "x");
		plane.y = atoi(tmp);
		tmp = strtok(NULL, "x");
		plane.x = atoi(tmp);
	}
	else
	{
		plane.x = 10;
		plane.y = 10;
	}

//Load PBM path
	if(getenv("EXIASAVER1_PBM") != NULL)
	{
		strcpy(path, getenv("EXIASAVER1_PBM"));
	}
	else
	{
		strcpy(path, ".");
	}
	strcat(path, "/");

//Init planes var
	char *planeBot = NULL;
	char *planeLeft = NULL;
	char *planeTop = NULL;
	char *planeRight = NULL;

	planeBot = malloc(512 * sizeof(char*));
	planeLeft = malloc(512 * sizeof(char*));
	planeTop = malloc(512 * sizeof(char*));
	planeRight = malloc(512 * sizeof(char*));

	loadPlane("planeBot.pbm", planeBot);
	loadPlane("planeLeft.pbm", planeLeft);
	loadPlane("planeTop.pbm", planeTop);
	loadPlane("planeRight.pbm", planeRight);

//Memory allocation
	for(i=0; i<row+1; i++)
		table[i] = malloc(col * sizeof(char));
	for(i=0; i<row+1; i++)
		for(j=0; j<col; j++)
	 		table[i][j] = ' ';

	system("clear");//Clear the terminal
	plane.sens=0;
	swapPlane(col, row, planeRight, table, plane);//Swap the plane in the table

	for(i=0; i<row+1; i++)
		for(j=0; j<col; j++)
	 		printf("%c", table[i][j]);
	while(1)
	{
		printf("x:%d y:%d", plane.x, plane.y);
		fflush(stdout);
		c = getch();
		//system("clear");
		switch (c)
		{
			case 'z':
				plane.x--;
				if(i<=-6) i=row-6;
				plane.sens = 0;
				swapPlane(col, row, planeTop, table, plane);
				break;
			case 'd':
				plane.y++;
				plane.sens = 1;
				swapPlane(col, row, planeRight, table, plane);
				break;
			case 's':
				plane.x++;
				plane.sens = 2;
				swapPlane(col, row, planeBot, table, plane);
				break;
			case 'q':
				plane.y--;
				plane.sens = 3;
				swapPlane(col, row, planeLeft, table, plane);
				break;
			case 'x':
				exit(0);
				break;
		}
		for(i=0; i<row; i++)
			for(j=0; j<col; j++)
	 			printf("%c", table[i][j]);
	}

	for(i=0; i<row+1; i++)
		free(table[i]);

	free(table);
	free(planeBot);
	free(planeTop);
	free(planeRight);
	free(planeLeft);
}


