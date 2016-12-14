#include <stdio.h>
#include <string.h>
#include <termios.h>

#include "lecture.h"

#define CHAR_PRINTED "#"

typedef struct plane plane;
	struct plane
	{
    	int x;
    	int y;
    	int sens;
	};

void loadPlane(char *path, char *plane)
{
	int size[2];
	char type[512];

	readPBM(path, size, type, plane);
}

void swapPlane(int col, int row, char *planeToPrint, char **table, plane plane)
{
	int i, j, n, k, l;
	char tmp[128];
	for(i=0; i<row; i++)
	{
		for(j=0; j<col; j++)
		{
	 		table[i][j] = ' ';
	 	}
	}

	i = 0;
	j = 0;
	for(n=0;n<strlen(planeToPrint);n++)
	{
		if(planeToPrint[n] == '1')//Put '1' in the table when there is '1' in the string
		{
			k=plane.x+j;
			l=plane.y+i-2;
			if(k<0) k = row + plane.x+1 + j;
			if(l>col) l = 0 + i + plane.y - col;
			if(k>row) k = 0 + j + plane.x - row;
			if(l<0) l = col + plane.y + i;
			table[k][l-3] = '#';
		}
		else if(planeToPrint[n] == '2')//Go to next row in the table
		{
			j++;
			i = -1;
		}
		i++;
	}
}

char getch()
{
	char ch;
	struct termios old, new;

	tcgetattr(0, &old); // grab old terminal i/o settings

	new = old; // new settings = old settings

	new.c_lflag &= ~ICANON; // disable buffered i/o
	//new.c_lflag &= ~ECHO; //set echo mode

	tcsetattr(0, TCSANOW, &new); // use these new terminal i/o settings now

	ch = getchar();

	tcsetattr(0, TCSANOW, &old); //restore old settings

	return ch;
}