/*
 * =====================================================================================
 *       Filename:  test.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2017年04月01日 16时04分46秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *   Organization:  
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#define	DEV_PATH "/dev/demo_dev"			/*  */
int main ( int argc, char *argv[] )
{
	int fd;
	char buf[64];
	char tmp[64]="11223399";
	fd = open(DEV_PATH,0600);
	if(fd<0){
		perror("can't open /dev/demo_dev");
		exit(-1);
	}

//	read(fd, buf, 64);
//	printf ( "buf=%s\n",buf );
	write(fd,tmp,strlen(tmp));
	return 0;
}
