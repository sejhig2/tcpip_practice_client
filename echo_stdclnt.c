/*
 * echo_stdclnt.c
 *
 *  Created on: 2023. 5. 11.
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

#define BUFSIZE (1024)

int main(int argc, char **argv)
{
	int sock = 0;
	FILE *read_fp = NULL;
	FILE *write_fp = NULL;
	char message[BUFSIZE] = { 0 };

	struct sockaddr_in serv_addr = { 0 }; /* 클라이언트의 주소구조체를 안 만드는 이유는 자동할당이기 때문*/

	if (argc != 3) {
		printf("Usage : %s <ip> <port>\n", argv[0]);
		exit(1);
	}

	sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		error_handling("socket() error");
	}

	/* 파일 디스크립터로 파일 포인터 생성 */
	read_fp = fdopen(sock, "r");
	write_fp = fdopen(sock, "w");

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(atoi(argv[2]));

	if (connect(sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1) {
		error_handling("connect() error");
	}

	while(1) {
		/* 메시지 입력 */
		fputs("전송할 메시지 입력(q to quit) : ", stdout);
		fgets(message, BUFSIZE, stdin);
		if (!strcmp(message, "q\n")) {
			break;
		}
		/* 메시지 전송 */
		fputs(message, write_fp);
		fflush(write_fp);

		/* 메시지 수신 */
		fgets(message, BUFSIZE, read_fp);
		printf("서버에서 전송된 메시지 : %s \n", message);
	}
	fclose(write_fp);
	fclose(read_fp);

	return 0;
}

