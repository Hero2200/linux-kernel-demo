#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>

int main(int argc, char **argv)
{
	int file_handler = 0;
	char *usage = "Usage: rwdev <r|w> <dev_file> <byte_count> [byte1] [byte2] ... [byten]";
	if (argc < 4)
	{
		printf("%s\n", usage);
		return 0;
	}
	char *cmd = argv[1];
	if (strcmp("r", cmd) != 0 && strcmp("w", cmd) != 0)
	{
		printf("%s\n", usage);
		return 0;
	}
	char *dev_filename = argv[2];
	int byte_count = atoi(argv[3]);
	unsigned char buf[byte_count];

	int i = 0;
	if (strcmp(cmd, "w") == 0)
	{
		for (; i < byte_count; i++)
		{
			buf[i] = atoi(argv[4 + i]);
		}
		file_handler = open(dev_filename, O_WRONLY);

		write(file_handler, buf, byte_count);
	}
	else if (strcmp(cmd, "r") == 0)
	{
		file_handler = open(dev_filename, O_RDWR);
		buf[0] = atoi(argv[4]);
		write(file_handler, buf, 1);
		read(file_handler, buf, byte_count);
		printf("%d bytes:", byte_count);
		for(; i < byte_count; i++)
		{
			printf("%d  ", buf[i]);
		}
		printf("\n");
	}
	close(file_handler);
	return 0;
}

