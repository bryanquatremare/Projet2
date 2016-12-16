#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header.h"

void assemblage(char *ligne, char *num0, char *num1, char *num2, char *num3, char *num4, char *num5, char *num6, char *num7, char *num8, char *num9, char *sep, char *space)
{
	int *heuredizaine = malloc(sizeof(int *));
	int *minutedizaine = malloc(sizeof(int *));
	int *secondedizaine = malloc(sizeof(int *));
	int *heureunite = malloc(sizeof(int *));
	int *minuteunite = malloc(sizeof(int *));
	int *secondeunite = malloc(sizeof(int *));
	int n = 0;
	int m = 0;
	int o = 0;
	int i = 0;
	char *tok = NULL;
	
	char ligneun[300], lignedeux[300], lignetrois[300], lignequatre[300], lignecinq[300];

	char un[300], deux[300], trois[300], quatre[300], cinq[300], six[300], spaceun[300], spacedeux[300], spacetrois[300], sepun[300], sepdeux[300]; 

	heurelocale(heuredizaine, heureunite, minutedizaine, minuteunite, secondedizaine, secondeunite);

	switch(*heuredizaine)//récupère la valeur de *heuredizaine et entre la chaine de caractere correspondante au  pbm adapté dans le deuxieme chiffre
	{
		case 1:
		strcpy(un, num1);
		break;

		case 2:	
		strcpy(un, num2);
		break;

		default:
		strcpy(un, num0);
		break;
	}
	

	switch(*heureunite) //
	{
		case 1:
		strcpy(deux, num1);
		break;

		case 2:
		strcpy(deux, num2);
		break;

		case 3:
		strcpy(deux, num3);
		break;

		case 4:
		strcpy(deux, num4);
		break;

		case 5:
		strcpy(deux, num5);
		break;

		case 6:
		strcpy(deux, num6);
		break;

		case 7:
		strcpy(deux, num7);
		break;

		case 8:
		strcpy(deux, num8);
		break;

		case 9:
		strcpy(deux, num9);
		break;

		default:
		strcpy(deux, num0);
		break;
	}

	switch(*minutedizaine) //
	{
		case 1:
		strcpy(trois, num1);
		break;

		case 2:
		strcpy(trois, num2);
		break;

		case 3:
		strcpy(trois, num3);
		break;

		case 4:
		strcpy(trois, num4);
		break;

		case 5:
		strcpy(trois, num5);
		break;

		default:
		strcpy(trois, num0);
		break;
	}

	switch(*minuteunite) //
	{
		case 1:
		strcpy(quatre, num1);
		break;

		case 2:
		strcpy(quatre, num2);
		break;

		case 3:
		strcpy(quatre, num3);
		break;

		case 4:
		strcpy(quatre, num4);
		break;

		case 5:
		strcpy(quatre, num5);
		break;

		case 6:
		strcpy(quatre, num6);
		break;

		case 7:
		strcpy(quatre, num7);
		break;

		case 8:
		strcpy(quatre, num8);
		break;
;
		case 9:
		strcpy(quatre, num9);
		break;

		default:
		strcpy(quatre, num0);
		break;
	}

	switch(*secondedizaine) //
	{
		case 1:
		strcpy(cinq, num1);
		break;

		case 2:
		strcpy(cinq, num2);
		break;

		case 3:
		strcpy(cinq, num3);
		break;

		case 4:
		strcpy(cinq, num4);
		break;

		case 5:
		strcpy(cinq,  num5);
		break;

		default:
		strcpy(cinq, num0);
		break;
	}

	switch(*secondeunite) //
	{
		case 1:
		strcpy(six, num1);
		break;

		case 2:
		strcpy(six, num2);
		break;

		case 3:
		strcpy(six, num3);
		break;

		case 4:
		strcpy(six, num4);
		break;

		case 5:
		strcpy(six, num5);
		break;

		case 6:
		strcpy(six, num6);
		break;

		case 7:
		strcpy(six, num7);
		break;

		case 8:
		strcpy(six, num8);
		break;

		case 9:
		strcpy(six, num9);
		break;

		default:
		strcpy(six, num0);
		break;
	}
	
	strcpy(spaceun, space);	// Ajout des chaines de caractères correspondantes aux caractères souhaités, afin que les mêmes chaînes "space" et "sep" ne soient pas manipulés plusieurs fois par les strtok dans une boucle.
	strcpy(spacedeux, space);
	strcpy(spacetrois, space);
	strcpy(sepun, sep);
	strcpy(sepdeux, sep);

	tok = strtok(un, "2"); //récupération et découpage des chaines de caractères dans de nouvelles chaines explicitement appelés ligneun, lignedeux, lignetrois, lignequatre et lignecinq
	if(tok != NULL)
		{
			sprintf(ligneun,"%s%s", ligneun, tok);
		}
	tok = strtok(NULL, "2");
	if(tok != NULL)
		{
			sprintf(lignedeux,"%s%s", lignedeux, tok);
		}
	tok = strtok(NULL, "2");
	if(tok != NULL)
		{
			sprintf(lignetrois,"%s%s", lignetrois, tok);
		}
	tok = strtok(NULL, "2");
	if(tok != NULL)
		{
			sprintf(lignequatre,"%s%s", lignequatre, tok);
		}
	tok = strtok(NULL, "2");
	if(tok != NULL)
		{
			sprintf(lignecinq,"%s%s", lignecinq,tok);	
		}

	
	tok = strtok(spaceun, "2"); // même chose pour chaque caractère qui sera a afficher
	if(tok != NULL)
		{
			sprintf(ligneun,"%s%s", ligneun, tok);
		}
	tok = strtok(NULL, "2");
	if(tok != NULL)
		{
			sprintf(lignedeux,"%s%s", lignedeux, tok);
		}
	tok = strtok(NULL, "2");
	if(tok != NULL)
		{
			sprintf(lignetrois,"%s%s", lignetrois, tok);
		}
	tok = strtok(NULL, "2");
	if(tok != NULL)
		{
			sprintf(lignequatre,"%s%s", lignequatre, tok);
		}
	tok = strtok(NULL, "2");
	if(tok != NULL)
		{
			sprintf(lignecinq,"%s%s", lignecinq, tok);
		}


	tok = strtok(deux, "2"); //
	if(tok != NULL)
		{
			sprintf(ligneun,"%s%s", ligneun, tok);
		}
	tok = strtok(NULL, "2");
	if(tok != NULL)
		{
			sprintf(lignedeux,"%s%s", lignedeux, tok);
		}
	tok = strtok(NULL, "2");
	if(tok != NULL)
		{
			sprintf(lignetrois,"%s%s", lignetrois, tok);
		}
	tok = strtok(NULL, "2");
	if(tok != NULL)
		{
			sprintf(lignequatre,"%s%s", lignequatre, tok);
		}
	tok = strtok(NULL, "2");
	if(tok != NULL)
		{
			sprintf(lignecinq,"%s%s", lignecinq, tok);
		}


	tok = strtok(sepun, "2"); //
	if(tok != NULL)
		{
			sprintf(ligneun,"%s%s", ligneun, tok);
		}
	tok = strtok(NULL, "2");
	if(tok != NULL)
		{
			sprintf(lignedeux,"%s%s", lignedeux, tok);
		}
	tok = strtok(NULL, "2");
	if(tok != NULL)
		{
			sprintf(lignetrois,"%s%s", lignetrois, tok);
		}
	tok = strtok(NULL, "2");
	if(tok != NULL)
		{
			sprintf(lignequatre,"%s%s", lignequatre, tok);
		}
	tok = strtok(NULL, "2");
	if(tok != NULL)
		{
			sprintf(lignecinq,"%s%s", lignecinq, tok);
		}


	tok = strtok(trois, "2"); //
	if(tok != NULL)
		{
			sprintf(ligneun,"%s%s", ligneun, tok);
		}
	tok = strtok(NULL, "2");
	if(tok != NULL)
		{
			sprintf(lignedeux,"%s%s", lignedeux, tok);
		}
	tok = strtok(NULL, "2");
	if(tok != NULL)
		{
			sprintf(lignetrois,"%s%s", lignetrois, tok);
		}
	tok = strtok(NULL, "2");
	if(tok != NULL)
		{
			sprintf(lignequatre,"%s%s", lignequatre, tok);
		}
	tok = strtok(NULL, "2");
	if(tok != NULL)
		{
			sprintf(lignecinq,"%s%s", lignecinq, tok);
		}


	tok = strtok(spacedeux, "2"); //
	if(tok != NULL)
		{
			sprintf(ligneun,"%s%s", ligneun, tok);
		}
	tok = strtok(NULL, "2");
	if(tok != NULL)
		{
			sprintf(lignedeux,"%s%s", lignedeux, tok);
		}
	tok = strtok(NULL, "2");
	if(tok != NULL)
		{
			sprintf(lignetrois,"%s%s", lignetrois, tok);
		}
	tok = strtok(NULL, "2");
	if(tok != NULL)
		{
			sprintf(lignequatre,"%s%s", lignequatre, tok);
		}
	tok = strtok(NULL, "2");
	if(tok != NULL)
		{
			sprintf(lignecinq,"%s%s", lignecinq, tok);
		}


	tok = strtok(quatre, "2"); //
	if(tok != NULL)
		{
			sprintf(ligneun,"%s%s", ligneun, tok);
		}
	tok = strtok(NULL, "2");
	if(tok != NULL)
		{
			sprintf(lignedeux,"%s%s", lignedeux, tok);
		}
	tok = strtok(NULL, "2");
	if(tok != NULL)
		{
			sprintf(lignetrois,"%s%s", lignetrois, tok);
		}
	tok = strtok(NULL, "2");
	if(tok != NULL)
		{
			sprintf(lignequatre,"%s%s", lignequatre, tok);
		}
	tok = strtok(NULL, "2");
	if(tok != NULL)
		{
			sprintf(lignecinq,"%s%s", lignecinq, tok);
		}


	tok = strtok(sepdeux, "2"); //
	if(tok != NULL)
		{
			sprintf(ligneun,"%s%s", ligneun, tok);
		}
	tok = strtok(NULL, "2");
	if(tok != NULL)
		{
			sprintf(lignedeux,"%s%s", lignedeux, tok);
		}
	tok = strtok(NULL, "2");
	if(tok != NULL)
		{
			sprintf(lignetrois,"%s%s", lignetrois, tok);
		}
	tok = strtok(NULL, "2");
	if(tok != NULL)
		{
			sprintf(lignequatre,"%s%s", lignequatre, tok);
		}
	tok = strtok(NULL, "2");
	if(tok != NULL)
		{
			sprintf(lignecinq,"%s%s", lignecinq, tok);
		}


	tok = strtok(cinq, "2"); //
	if(tok != NULL)
		{
			sprintf(ligneun,"%s%s", ligneun, tok);
		}
	tok = strtok(NULL, "2");
	if(tok != NULL)
		{
			sprintf(lignedeux,"%s%s", lignedeux, tok);
		}
	tok = strtok(NULL, "2");
	if(tok != NULL)
		{
			sprintf(lignetrois,"%s%s", lignetrois, tok);
		}
	tok = strtok(NULL, "2");
	if(tok != NULL)
		{
			sprintf(lignequatre,"%s%s", lignequatre, tok);
		}
	tok = strtok(NULL, "2");
	if(tok != NULL)
		{
			sprintf(lignecinq,"%s%s", lignecinq, tok);
		}


	tok = strtok(spacetrois, "2"); //
	if(tok != NULL)
		{
			sprintf(ligneun,"%s%s", ligneun, tok);
		}
	tok = strtok(NULL, "2");
	if(tok != NULL)
		{
			sprintf(lignedeux,"%s%s", lignedeux, tok);
		}
	tok = strtok(NULL, "2");
	if(tok != NULL)
		{
			sprintf(lignetrois,"%s%s", lignetrois, tok);
		}
	tok = strtok(NULL, "2");
	if(tok != NULL)
		{
			sprintf(lignequatre,"%s%s", lignequatre, tok);
		}
	tok = strtok(NULL, "2");
	if(tok != NULL)
		{
			sprintf(lignecinq,"%s%s", lignecinq, tok);
		}


	tok = strtok(six, "2"); //
	if(tok != NULL)
		{
			sprintf(ligneun,"%s%s", ligneun, tok);
		}
	tok = strtok(NULL, "2");
	if(tok != NULL)
		{
			sprintf(lignedeux,"%s%s", lignedeux, tok);
		}
	tok = strtok(NULL, "2");
	if(tok != NULL)
		{
			sprintf(lignetrois,"%s%s", lignetrois, tok);
		}
	tok = strtok(NULL, "2");
	if(tok != NULL)
		{
			sprintf(lignequatre,"%s%s", lignequatre, tok);
		}
	tok = strtok(NULL, "2");
	if(tok != NULL)
		{
			sprintf(lignecinq,"%s%s", lignecinq, tok);
		}

	sprintf(ligne,"%s2%s2%s2%s2%s", ligneun, lignedeux, lignetrois, lignequatre, lignecinq); // assemble toutes les lignes dans l'ordre et séparées par un 2 qui permettra au programme suivant de repérer les sauts de ligne
	strcpy(ligneun, ""); //réinitialisation des char des lignes
	strcpy(lignedeux, "");
	strcpy(lignetrois, "");
	strcpy(lignequatre, "");
	strcpy(lignecinq, "");
		
	
	free(heuredizaine); //libérations des espaces réservés aux pointeurs de cette fonction
	free(heureunite);
	free(minutedizaine);
	free(minuteunite);
	free(secondedizaine);
	free(secondeunite);
}