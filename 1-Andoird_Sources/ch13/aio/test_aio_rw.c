#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <aio.h>
#include <errno.h>
#define BUFFER_SIZE  2000
#define MAX_LIST 1
int main()
{
	int fd;
	int ret;
	struct aiocb my_aiocb;
	const struct aiocb *cblist[MAX_LIST];
	char *str = "I love you.";

	fd = open("./test_aio_rw.c", O_RDONLY);

	if(fd < 0)
	{
		perror("open");
	}
	bzero((void*)&my_aiocb, sizeof(struct aiocb));
	bzero((void*)cblist, sizeof(cblist));
	cblist[0] = &my_aiocb;
	my_aiocb.aio_buf = malloc(BUFFER_SIZE + 1);
	if(!my_aiocb.aio_buf)
	{
		perror("malloc");
	}
	my_aiocb.aio_fildes = fd;
	my_aiocb.aio_nbytes = BUFFER_SIZE;
	my_aiocb.aio_offset = 0;

    ret = aio_read(&my_aiocb);
    if(ret < 0)
    	perror("aio_read");
    ret = aio_suspend(cblist, MAX_LIST, NULL);
    if((ret < 0))
    	perror("suspend");
    if(aio_error(&my_aiocb) != 0)
        perror("aio_read");
    if((ret = aio_return(&my_aiocb)) > 0)
    {
    	printf("%s\n", (char*)my_aiocb.aio_buf);
    }
    close(fd);

    fd = open("./test.txt", O_WRONLY);
	if(fd < 0)
	{
		perror("open");
	}
    bzero((void*)&my_aiocb, sizeof(struct aiocb));
	my_aiocb.aio_fildes = fd;
	my_aiocb.aio_nbytes = strlen(str);
	my_aiocb.aio_offset = 0;

	my_aiocb.aio_buf = str;

	ret = aio_write(&my_aiocb);
	if(ret < 0)
	  perror("aio_write");

	while(aio_error(&my_aiocb) == EINPROGRESS);
    if((ret = aio_return(&my_aiocb)) > 0)
    {
    	printf("write success!\n");
    }

    close(fd);
}
