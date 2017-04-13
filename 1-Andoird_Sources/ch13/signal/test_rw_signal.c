#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#define LENGTH 100
int fd;
void signal_handler(int signo)
{
	static count = 0;
	fd_set rfds, wfds;
	char buf[LENGTH];
	memset(buf, 0, LENGTH);

	FD_ZERO(&rfds);
	FD_ZERO(&wfds);
	FD_SET(fd, &rfds);
	FD_SET(fd, &wfds);

	select(fd + 1, &rfds, &wfds, NULL, NULL);
	/*数据可获得*/
	if (FD_ISSET(fd, &rfds))
	{
		printf("Data can be read!\n");
		read(fd, buf, LENGTH);
		printf("string:%s\n", buf);
	}
	/*数据可写入*/
	if (FD_ISSET(fd, &wfds))
	{
		printf("Data can be written\n");
	}

	printf("signal:%d\n", signo);
	printf("count:%d\n", ++count);
	printf("-------------------\n");

}

int main()
{
	int flags;
	fd = open("/dev/signal", O_RDWR);
	if (fd > 0)
	{
		signal(SIGIO, signal_handler);
		fcntl(fd, F_SETOWN, getpid());
		flags = fcntl(fd, F_GETFL);
		fcntl(fd, F_SETFL, flags | FASYNC);
		while (1)
		{
			sleep(100);
		}
	}

}

