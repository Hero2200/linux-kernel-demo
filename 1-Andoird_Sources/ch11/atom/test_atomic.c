#include <stdio.h>
#include <errno.h>
int main()
{
	int handler = open("/dev/atomic", 0);
	printf("handler:%d\n", handler);

	if (handler > 0)
	{
		getchar();
		close(handler);
	}
	else
	{
		printf("errno:%d\n", errno);
	}
}
