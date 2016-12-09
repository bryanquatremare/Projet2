#include <stdlib.h> // routines standards
#include <stdio.h> // traitement entrées/sortie
#include <string.h> // tratement de chaine de caractères
#include <sys/ioctl.h> // control devices (like terminals)
#include <unistd.h> // type et constante symboles standard
#include <math.h> // traitement mathématique
#include <errno.h> // traitement des erreurs
#include <sys/wait.h> // définitions d'attentes
#include <sys/types.h> // définitions de temps
#include <termios.h>

#define MAXLINE 1024

char *readImage(char *file, char *image, int *taille) //Retourne le type (P1, P2 ...), la largeur et la hauteur de l'image
{
	struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);  // permet de récupérer la taille de la console

	char line[MAXLINE];
	char *p = NULL;
	char *center = NULL;
	char type[2];
	int i;
	int height = w.ws_row;
	int width = w.ws_col;
	FILE *fp;


	fp = fopen(file, "r");

	i = 0;
	if (fp != NULL) //Si on réussit à ouvrir le fichier
	{
		while(i<2)
		{
			if(fgets(line,sizeof(line),fp)!= NULL) //On vérifie que la première ligne du fichier n'est pas NULL (vide)
			{
				line[strcspn(line, "\n")] = '\0'; // on remplace le caractère de retour charriot par un fin de ligne

				if(strncmp(line, "#", 1) != 0) //On vérifie le PREMIER (1) caractère pour ignorer les commentaires
				{
					if (i) //Si on a deja fait un tour on est à la ligne de la largeur/hauteur
					{
						p = strtok(line, " ");
						taille[0] = atoi(p);
						p = strtok(NULL, " ");
						taille[1] = atoi(p);
					}
					else //Sinon on est à la ligne du type de l'image
					{
						strcpy(type, line);
					}
					i++;
				}
			}
		}

		width = floor((width - taille[0]) / 2); //On calcul le pas pour centrer notre image
		height = floor((height - taille[1]) / 2);//Meme chose verticalement
	    
	    center = malloc(sizeof(char *) * width);

	    for(i=0; i<width; i++) //On crée la chaine de caracteres center contenant les espaces qui permettent de centrer notre image
	    {
	    	strcat(center, " ");
	    }

		image = malloc(sizeof(char *) * taille[0] * taille[1] * strlen(center) * taille[1] * height);
		strcpy(image, "");

		for(i=0; i<height; i++) //On crée la chaine de caracteres center contenant les espaces qui permettent de centrer notre image
	    {
	    	strcat(image, "\n");
	    }

		while(fgets(line,sizeof(line),fp)!= NULL)
		{
			p = strtok(line, " ");
			strcat(image, center); //On ajoute notre chaine center a chaque debut de ligne de l'image
			while(p != NULL)
    		{
				if(strncmp(p, "0", 1) == 0)
				{
					strcat(image, " ");
				}
				else if(strncmp(p, "1", 1) == 0)
				{
					strcat(image, "\u2588");
				}
				p = strtok(NULL, " ");
			}
			strcat(image, "\n");
		}
		fclose(fp);
		free(center);
		taille[2] = height;
		return image;
	}
	else //Si on ne peut pas ouvrir le fichier on affiche une erreur
	{
		printf("Erreur pendant la lecture de l'image\n");
		exit(EXIT_FAILURE);
	}
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
	if(argc == 1) //Si il n'y a aucun paramètre, renvoyer une erreur
	{
		printf("Paramètre incorrect: veuillez entrer le chemin vers le .pbm.\n");
		return -1;
	}
	char *image = NULL;
	int taille[3];
	char chemin[256];
	int i, pid;
	FILE *f;

	if(getenv("EXIASAVER1_PBM") != NULL) //Si la variable existe alors on entre sa valeur dans le chemin sinon on utilise le repertoire courant
	{
		strcpy(chemin, getenv("EXIASAVER1_PBM"));
	}
	else
	{
		strcpy(chemin, ".");
	}
	strcat(chemin, "/");
	strcat(chemin, argv[1]); //On finit d'ecrire le chemin

	pid = fork(); //On fork

	switch(pid)
	{
		case -1:
			perror("fork");
			exit(EXIT_FAILURE);
			break;
		case 0:
			image = readImage(chemin, image, taille);
			system("clear");
			printf("%s", image);
			break;
		default:
			wait(NULL);
			getch();
			system("clear");
			break;
	}
<<<<<<< HEAD
	f = fopen("./.test.sh", "w+"); // création d'un script de pause et ouverture du flux d'écriture
	fprintf(f, "#!/bin/bash\n"); // écriture de la première ligne du script
	fprintf(f, "read -n 1"); // écriture de la deuxième ligne
	fclose(f); // fermeture du flux d'écriture 
	system("./.test.sh"); // ouverture du script de pause
	system("clear"); // a l'appui d'une touche, clear l'écran
	remove(".test.sh"); // supprimer le script de pause
	
	return 0;
=======
	free(image);
	return 0;	
>>>>>>> origin/master
}