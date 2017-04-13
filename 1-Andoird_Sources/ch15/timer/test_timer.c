#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>

main()
{
  int fd;
  int counter = 0;
  int old_counter = 0;

  /*打开/dev/timer_demo设备文件*/
  fd = open("/dev/timer_demo", O_RDONLY);
  if (fd !=  - 1)
  {
    while (1)
    {
      read(fd,&counter, sizeof(unsigned int));
      if(counter!=old_counter)
      {
      	printf("seconds after open /dev/timer_demo :%d\n",counter);
      	old_counter = counter;
      }
    }
  }
  else
  {
    printf("Device open failure\n");
  }
}
