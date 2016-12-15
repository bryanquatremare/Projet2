#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int typeLine(char **table, int i);//Get the type of the i line of the file

int lineNumber();//Get the number of line of the historic

int num(char *str);//Transform the date in a timestamp

char **histoToTable(char **table);//Put the historique file in a 2D table

void triDate(char **table);//Sort by increasing dates

void reverseTriDate(char **table);//Sort by decreasing dates

void triType(char **table);//Sort by type

void printHisto(char **table); //Print the historic
