#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>




int main()
{	
	system("clear");
	int i;
	int n;
	printf("Entrer le nombre de secondes avant refresh... ");
	scanf("%d", &n);
	while(1)
	{
		printf("Cet écran sera actualisé dans quelques secondes ");
		fflush(stdout);
		i = 0;
		while(i < n)
		{
			
			sleep(1);
			printf(". ");
			fflush(stdout);
			i++;
		}
		system("clear");		
	}
}