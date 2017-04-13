#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>   // 该头文件可以不include，只为了可以跟踪ioctl才include该头文件

int main(int argc, char **argv)
{
	int file_handler = 0;
	int cmd = 0;
	int arg = 0;
	if(argc < 4)
	{
		printf("Usage: ioctl <dev_file> <cmd> <arg>\n");
		return 0;
	}
	cmd = atoi(argv[2]);
	arg = atoi(argv[3]);
	printf("dev:%s\n", argv[1]);
	printf("cmd:%d\n", cmd);
	printf("arg:%d\n", arg);
	file_handler = open(argv[1], 0);

	ioctl(file_handler, cmd, arg);
	close(file_handler);
	return 0;
}

