#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <aio.h>
#include <errno.h>
#define BUFFER_SIZE 100
void aio_completion_handler( sigval_t sigval )
{
	int ret;
	struct aiocb *my_aiocb;
	my_aiocb = (struct aiocb *)sigval.sival_ptr;
	if ((ret = aio_return(my_aiocb)) > 0)
	{
		printf("value:%s\n", (char*) (my_aiocb->aio_buf));
	}

}


int main()
{
	int ret;
	int fd;
	struct aiocb my_aiocb;
	fd = open("/dev/aio_signal", O_RDWR);
	if (fd < 0)
	{
		perror("open");
	}
	bzero((void*) &my_aiocb, sizeof(struct aiocb));
	my_aiocb.aio_buf = malloc(BUFFER_SIZE + 1);
	if (!my_aiocb.aio_buf)
	{
		perror("malloc");
	}
	my_aiocb.aio_fildes = fd;
	my_aiocb.aio_nbytes = BUFFER_SIZE;
	my_aiocb.aio_offset = 0;

	my_aiocb.aio_sigevent.sigev_notify = SIGEV_THREAD;
	my_aiocb.aio_sigevent._sigev_un._sigev_thread._function = aio_completion_handler;
	my_aiocb.aio_sigevent._sigev_un._sigev_thread._attribute = NULL;
	my_aiocb.aio_sigevent.sigev_value.sival_ptr = &my_aiocb;

	ret = aio_read(&my_aiocb);
	if (ret < 0)
		perror("aio_read");

    sleep(1);

}

