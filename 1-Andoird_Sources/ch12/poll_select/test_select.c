#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>

#define BUFFER_LEN 20
int main()
{
	int fd, num;
	fd_set rfds, wfds;
    char buf[BUFFER_LEN];
    memset(buf, 0, BUFFER_LEN);
	fd = open("/dev/poll_select", O_RDWR | O_NONBLOCK);
	if (fd != -1)
	{


		while (1)
		{
			FD_ZERO(&rfds);
			FD_ZERO(&wfds);
			FD_SET(fd, &rfds);
			FD_SET(fd, &wfds);

			select(fd + 1, &rfds, &wfds, NULL, NULL);
			/*数据可获得*/
			if (FD_ISSET(fd, &rfds))
			{
				printf("Data can be read!\n");
		        read(fd, buf, BUFFER_LEN);
				printf("value:%s\n", buf);
			    memset(buf, 0, BUFFER_LEN);
			}
			/*数据可写入*/
			if (FD_ISSET(fd, &wfds))
			{
				printf("Data can be written\n");
			}
			sleep(1);

		}
	}
	else
	{
		printf("Device open failure\n");
	}
}
