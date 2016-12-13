#include <stdio.h>

void centre(int *axeconsole, int axepbm)
{
printf("axeconsole = %d", *axeconsole);
int n = 1;
while(n != (*axeconsole/2)-(axepbm/2))
	{	
		printf("axeconsole = %d", *axeconsole);
		printf("\n");
		n++;
	}

	if((*axeconsole/2)-(axepbm/2) % 2 != 0)
	{
		printf("axepbm = %d", axepbm);
		printf("\n");
	}
}