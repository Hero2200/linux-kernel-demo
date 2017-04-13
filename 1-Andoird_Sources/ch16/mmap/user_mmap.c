#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/mman.h>
#include <stdio.h>
#define PAGE_SIZE (4*1024)
int main()
{
	int fd;
	void *start;


	fd = open("/dev/mmap_shared", O_RDWR);
	start = mmap(NULL, PAGE_SIZE, PROT_READ, MAP_PRIVATE, fd, 0);

	if (start == MAP_FAILED)
	{
		printf("mmap error\n");
		return 0;
	}
	puts(start);
	munmap(start, PAGE_SIZE);
	close(fd);
}
