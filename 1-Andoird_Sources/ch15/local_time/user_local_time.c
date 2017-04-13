#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>


int main()
{
	struct timeval tv;

	struct tm time;

	int i = 0;
	while (i < 5)
	{
	    gettimeofday(&tv, NULL);
	    printf("sec:%ld\n", tv.tv_sec);
 	    sleep(1);
	    i++;
	}
	time.tm_year = 2011;
	time.tm_mon = 10;
	time.tm_mday = 20;
	time.tm_hour = 12;
	time.tm_min = 12;
	time.tm_sec = 14;


	tv.tv_sec= mktime(&time);
	printf("setting time:%d\n", settimeofday(&tv, NULL));

}
