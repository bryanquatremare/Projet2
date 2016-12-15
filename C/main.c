#include <stdlib.h>//Basic functions
#include <stdio.h>//Input/Output
#include <string.h>//String manipulation
#include <sys/ioctl.h>//Get terminal size
#include <time.h>//Random

#include "plane.h"//Plane library
#include "PBM.h"//PBM library

typedef struct plane plane; //Init the plane structure
	struct plane
	{
    	int x;
    	int y;
    	int direction;
	};

int main(int argc, char *argv[])
{
//Load terminal size
	struct winsize w;
	ioctl(1, TIOCGWINSZ, &w);
	int col = w.ws_col;
	int row = w.ws_row;

//Init some var
	int i, j, redo;
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

		if(plane.x<=-6) plane.x=row-6;
		if(plane.y>=col-6) plane.y=-6;
		if(plane.x>=row-6) plane.x=-6;
		if(plane.y<=-6) plane.y=col-6;
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

//Init planes var and load planes
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

//Memory allocation of our 2D table
	for(i=0; i<row+1; i++)
		table[i] = malloc(col * sizeof(char));

	for(i=0; i<row+1; i++)
		for(j=0; j<col; j++)
	 		table[i][j] = ' ';

	srand(time(NULL));//Generate a random direction
	plane.direction = rand()%(4);

	switch(plane.direction) //Move the plane in the table
	{
		case 0:
			swapPlane(col, row, planeTop, table, plane);//Top
			break;
		case 1:
			swapPlane(col, row, planeRight, table, plane);//Right
			break;
		case 2:
			swapPlane(col, row, planeBot, table, plane);//Bot
			break;
		case 3:
			swapPlane(col, row, planeLeft, table, plane);//Left
			break;
	}

	for(i=0; i<row; i++) //Print the 2D table
		for(j=0; j<col; j++)
	 		printf("%c", table[i][j]);

	while(1)
	{
		c = getch(); //Get user input
		do
		{
			if(redo) redo = 0;//We do not want the loop to be infinite
			switch (c)
			{
				case 'z': //If z is pressed, the plane goes up
					plane.x--;
					if(plane.x<=-6) plane.x=row-6;
					plane.direction = 0;
					swapPlane(col, row, planeTop, table, plane);
					break;
				case 'd'://If d is pressed, the plane goes right
					plane.y++;
					if(plane.y>=col-6) plane.y=-6;
					plane.direction = 1;
					swapPlane(col, row, planeRight, table, plane);
					break;
				case 's'://If s is pressed, the plane goes down
					plane.x++;
					if(plane.x>=row-6) plane.x=-6;
					plane.direction = 2;
					swapPlane(col, row, planeBot, table, plane);
					break;
				case 'q': //If q is pressed, the plane goes left
					plane.y--;
					if(plane.y<=-6) plane.y=col-6;
					plane.direction = 3;
					swapPlane(col, row, planeLeft, table, plane);
					break;
				case 'x'://If q is pressed we quit the program
					system("clear");
					exit(0);
					break;
				default://If another key is pressed the plane continue to move in his last direction
					switch(plane.direction)
					{
						case 0:
							c = 'z';
							break;
						case 1:
							c = 'd';
							break;
						case 2:
							c = 's';
							break;
						case 3:
							c = 'q';
							break;
					}
					redo = 1;//We do the loop a second time if the user pressed another key than zqsd or x

			}
		} while (redo);//While we need to do the loop

		for(i=0; i<row; i++)//Print the 2D table
			for(j=0; j<col; j++)
	 			printf("%c", table[i][j]);
	}

	system("clear");

	//Free memory
	for(i=0; i<row+1; i++)
		free(table[i]);

	free(table);
	free(planeBot);
	free(planeTop);
	free(planeRight);
	free(planeLeft);
}


