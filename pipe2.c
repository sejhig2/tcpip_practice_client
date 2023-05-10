/*
 * pip2.c
 *
 *  Created on: 2023. 5. 10.
 *      Author: jhhwang
 */


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFSIZE				(30)

int main(int argc, char ** argv)
{
	int fd[2] = {0};
	char buffer[BUFSIZE] = {0};
	pid_t pid = 0;
	int state = 0;

	state = pipe(fd);
	if(state == -1)
	{
		puts("pipe() error\n");
		exit(1);
	}

	pid = fork();
	if(pid == -1)
	{
		puts("fork() error\n");
		exit(1);
	} else if(pid == 0)
	{
		/* 자식 프로세스인 경우*/
		write(fd[1],"Good!",6); /*입력 파일 디스크립트를 통해서 전송하기 */
		sleep(2);
		read(fd[0], buffer, BUFSIZE); /*출력 파일 디스크립트를 통해서 출력된 내용 읽어들이기 */
		printf("자식 프로세스 출력 : %s \n\n",buffer);
	} else {
		/* 부모 프로세스인 경우 */
		read(fd[0],buffer, BUFSIZE); /* 출력 파일 디스크립트를 통해서 출력된 내용 읽어들이기 */
		printf("부모 프로세스 출력 : %s \n",buffer);
		write(fd[1], "really good",12); /* 입력 파일 디스크립트를 통해서 입력하고 송신하기 */
		sleep(3);
	}
	/* 자식 프로세스는 어디서 종료시키나? */
	printf("done!\n");
	return 0;
}
