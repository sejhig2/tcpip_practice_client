/*
 * echo_multiclnt.c
 *
 *  Created on: 2023. 5. 9.
 *      Author: jhhwang
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "error_handling.h"

#define BUFSIZE (30)

int main(int argc, char **argv)
{
	int sock = 0;
	pid_t pid = 0;
	char message[BUFSIZE] = { 0 };
	int str_len = 0;
	//int recv_len = 0;
	//int recv_num = 0;
	struct sockaddr_in serv_addr = { 0 };

	if (argc != 3) {
		printf("Usage : %s <ip> <port> \n", argv[0]);
		exit(1);
	}

	sock = socket(PF_INET, SOCK_STREAM, 0);

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(atoi(argv[2]));

	if (connect(sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1) {
		error_handling("connect() error!");
	}

	pid = fork();
	/*부모 프로세스는 수신, 자식 프로세스는 송신 */
	if (pid == 0) {
		/*자식 프로세스 : 메시지 전송*/
		while(1) {
			fputs("전송할 메시지를 입력하세요 (q to quit): \n", stdout);
			fgets(message, BUFSIZE, stdin);

			if (!strcmp(message, "q\n")) {
				shutdown(sock, SHUT_WR);
				close(sock);
				exit(0);
			}

			write(sock, message, strlen(message));
		}/*while(1) end*/
	} /* if(pid == 0) end */
	else {
		/* 부모 프로세스 : 메시지 수신*/
		while(1) {
			int str_len = read(sock, message, BUFSIZE);
			if (str_len = 0) {
				exit(0);
			}

			message[str_len] = 0;
			printf("서버에서 전송된 메시지 : %s \n", message);
		}
	}
	close(sock);

	return 0;
}
