#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void main()
{
	time_t timer;
	struct tm * t;

	time(&timer);


	t = localtime(&timer);
	printf("%02uh %02um %02us\n", t->tm_hour, t->tm_min, t->tm_sec);
}
