/*
 * pipe1.c
 *
 *  Created on: 2023. 5. 10.
 *      Author: jhhwang
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFSIZE (30)

int main(int agrc, char **argv)
{
	int fd[2] = {0};
	char buffer[BUFSIZE] = {0};
	pid_t pid = 0;
	int state = 0;

	state = pipe(fd);

	if(pid == 1)
	{
		puts("fork() error\n");
		exit(1);
	} else if(pid == 0){
		write(fd[1], "good\n",6);
	} else {
		read(fd[0], buffer, BUFSIZE);
		puts(buffer);
	}


	return 0;
}
