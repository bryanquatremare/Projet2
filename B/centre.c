#include <stdio.h>

void centre(int *axeconsole, int axepbm)
{
int n = 1;
while(n != (*axeconsole/2)-(axepbm/2))
	{	
		printf("\n");
		n++;
	}

	if((*axeconsole/2)-(axepbm/2) % 2 != 0)
	{
		printf("\n");
	}
}