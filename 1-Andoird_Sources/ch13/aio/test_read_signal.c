#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <aio.h>
#include <errno.h>
#define BUFFER_SIZE 100
#define MAX_LIST 1
struct aiocb my_aiocb;
const struct aiocb *cblist[MAX_LIST];

void signal_handler(int signo)
{

	int ret;
	ret = aio_read(&my_aiocb);
	if (ret < 0)
		perror("aio_read");
	ret = aio_suspend(cblist, MAX_LIST, NULL);
	if ((ret < 0))
		perror("suspend");
	if ((ret = aio_return(&my_aiocb)) > 0)
	{
		printf("value:%s\n", (char*) my_aiocb.aio_buf);
		memset((char*) my_aiocb.aio_buf, 0, BUFFER_SIZE);
	}
}

int main()
{
	int flags;
	int ret;
	int fd;
	fd = open("/dev/aio_signal", O_RDWR);
	if (fd < 0)
	{
		perror("open");
	}
	bzero((void*) &my_aiocb, sizeof(struct aiocb));
	bzero((void*) cblist, sizeof(cblist));
	cblist[0] = &my_aiocb;
	my_aiocb.aio_buf = malloc(BUFFER_SIZE + 1);
	if (!my_aiocb.aio_buf)
	{
		perror("malloc");
	}
	my_aiocb.aio_fildes = fd;
	my_aiocb.aio_nbytes = BUFFER_SIZE;
	my_aiocb.aio_offset = 0;

	signal(SIGIO, signal_handler);
	fcntl(fd, F_SETOWN, getpid());
	flags = fcntl(fd, F_GETFL);
	fcntl(fd, F_SETFL, flags | FASYNC);

	while (1)
	{
		sleep(100);
	}

}

