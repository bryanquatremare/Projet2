#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <termios.h>

typedef struct avion avion;
	struct avion
	{
    	int x;
    	int y;
    	int sens;
	};

void changeAvion(char **tableau, int sens, avion avion)
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
				tableau[avion.x+j][avion.y+i] = '#';
			}
			p = strtok(NULL, " ");
			i++;
		}
		j++;
		i = 0;
	}
	fclose(fp);
	
}

char getch()
{
    char buf=0;
    struct termios old={0};
    fflush(stdout);
    if(tcgetattr(0, &old)<0)
        perror("tcsetattr()");
    old.c_lflag&=~ICANON;
    old.c_lflag&=~ECHO;
    old.c_cc[VMIN]=1;
    old.c_cc[VTIME]=0;
    if(tcsetattr(0, TCSANOW, &old)<0)
        perror("tcsetattr ICANON");
    if(read(0,&buf,1)<0)
        perror("read()");
    old.c_lflag|=ICANON;
    old.c_lflag|=ECHO;
    if(tcsetattr(0, TCSADRAIN, &old)<0)
        perror ("tcsetattr ~ICANON");
    printf("%c\n",buf);
    return buf;
}

int main(int argc, char *argv[])
{
	struct winsize w;

	avion avion;

	avion.x = 20;
	avion.y = 40;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int col = w.ws_col;
	int row = w.ws_row;
	int i;
	int j;
	char **tableau = malloc(col * row * sizeof(char*));
	char c = ' ';

	for(i=0; i<row; i++)
	{
		tableau[i] = malloc(col * row * sizeof(char));
	}
	for(i=0; i<row; i++)
	{
		for(j=0; j<col; j++)
		{
	 		tableau[i][j] = ' ';
	 	}
	}
	system("clear");
	changeAvion(tableau, 2, avion);
	for(i=0; i<row; i++)
	{
		for(j=0; j<col; j++)
		{
	 		printf("%c", tableau[i][j]);
	 	}
	}
	while(1)
	{
		c = getch();
		system("clear");
		if(c == 'q')
			exit(0);
		printf("%c", c);
		// for(i=0; i<row; i++)
		// {
		// 	for(j=0; j<col; j++)
		// 	{
	 // 			printf("%c", tableau[i][j]);
	 // 		}
		// }
	}
	for(i=0; i<row; i++)
	{
		free(tableau[i]);
	}
	free(tableau);
}