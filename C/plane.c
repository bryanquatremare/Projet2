#include <stdio.h>//Input / Output
#include <string.h>//String manipulation
#include <termios.h>//Terminal I/O manipulation

#include "PBM.h" //PBM lib

typedef struct plane plane;//Init the plane structure
	struct plane
	{
    	int x;
    	int y;
    	int direction;
	};

void loadPlane(char *path, char *plane)//Load a plane in *plane from *path
{
	int size[2];
	char type[512];

	readPBM(path, size, type, plane);
}

void swapPlane(int col, int row, char *planeToPrint, char **table, plane plane)//Move the plane to his new coord
{
	int i, j, n, k, l;
	char tmp[128];

	for(i=0; i<row; i++) //Empty the table
	{
		for(j=0; j<col; j++)
		{
	 		table[i][j] = ' ';
	 	}
	}

	i = 0; 
	j = 0; 
	for(n=0;n<strlen(planeToPrint);n++)//For all char in planeToPrint
	{
		if(planeToPrint[n] == '1')//Put '1' in the table when there is '1' in the string
		{
			k=plane.x+j; // k = row number
			l=plane.y+i; // l = collumn number
			if(k<0) k = row + k;
			if(l<0) l = col + l;
			table[k][l] = '#';
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
	new.c_lflag &= ~ECHO; //set echo mode

	tcsetattr(0, TCSANOW, &new); // use these new terminal i/o settings now

	ch = getchar();

	tcsetattr(0, TCSANOW, &old); //restore old settings

	return ch;
}