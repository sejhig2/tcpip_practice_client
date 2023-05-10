/*
 * pipe3.c
 *
 *  Created on: 2023. 5. 10.
 *      Author: jhhwang
 *      목표 : 프로세스간 통신할 때 송수신 전용 파이프를 만들어 오류를 제어한다.
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFSIZE (30)

int main(int argc, char **argv)
{
	int fd1[2] = { 0 };
	int fd2[2] = { 0 };
	char buffer[BUFSIZE] = { 0 };
	pid_t pid = 0;

	if ((pipe(fd1) == -1) || (pipe(fd2) == -1)) {
		puts("pipe() error\n");
		exit(1);
	}

	pid = fork();

	/*
	 *  child    1>===fd1===>0 parent
	 *  child		0<===fd2===<1 parent
	 */
	if (pid == -1) {
		puts("fork() error \n");
		exit(1);
	} else if (pid == 0) {
		/* 자식 프로세스인 경우*/
		write(fd1[1], "good!", 6);
		read(fd2[0], buffer, BUFSIZE);
		printf("자식 프로세스 출력 : %s \n\n", buffer);
	} else {
		/* 부모 프로세스인 경우*/
		read(fd1[0], buffer, BUFSIZE);
		printf("부모 프로세스 출력 %s \n\n", buffer);
		write(fd2[1], "really good", 12);
		sleep(1);
	}

	return 0;
}
