#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>

void signal_handler(int signo)
{
	printf("Have caught signal N.O. %d\n", signo);
}

int main()
{
	printf("process id is %d\n", getpid());
	signal(SIGINT, signal_handler);
	signal(SIGHUP, signal_handler);
	signal(SIGQUIT, signal_handler);
	getchar();
}
