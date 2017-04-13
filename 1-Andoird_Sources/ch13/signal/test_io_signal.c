#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#define LENGTH 100
void signal_handler(int signo)
{
	int len;
	  sigset_t    sigset;
	char data[LENGTH];
	len = read(STDIN_FILENO, &data, LENGTH);
	data[len] = 0;
	printf("string:%s\n", data);

}

int main()
{
	int flags=SA_RESTART;
	struct sigaction sigaction_struct;
	sigaction_struct.sa_handler = signal_handler;
	sigaction(SIGIO,&sigaction_struct, NULL);
	fcntl(STDIN_FILENO, F_SETOWN, getpid());
	flags = fcntl(STDIN_FILENO, F_GETFL);
	fcntl(STDIN_FILENO, F_SETFL, flags | FASYNC);
	while(1)
	{
		sleep(100);
	}

}
