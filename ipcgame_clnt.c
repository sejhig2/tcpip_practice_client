/*
 * ipcgame_clnt.c
 *
 *  Created on: 2023. 5. 10.
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

#define BUFSIZE (100)

int main(int argc, char ** argv)
{
	int sock = 0;
	char message[BUFSIZE] = {0};
	int str_len = 0;

	struct sockaddr_in serv_addr = {0};

	if(argc != 3)
	{
		printf("Usage : %s <ip> <port> \n",argv[0]);
		exit(1);
	}

	sock = socket(PF_INET, SOCK_STREAM, 0);

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(atoi(argv[2]));

	if( connect(sock,(struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){
		error_handling("connect error");
	}

	/* 가위 바위 보 게임 시작 */
	str_len = read(sock, message, BUFSIZE -1);
	message[str_len] = 0;
	fputs(message, stdout);
	fflush(stdout);

	str_len = read(0, message, BUFSIZE); /* 클라이언트 선택 입력 */
	write(sock, message, str_len); /* 클라이언트 선택을 서버에 전송 */

	str_len = read(sock, message, BUFSIZE -1);
	message[str_len] = 0;
	puts(message);

	close(sock);

	return 0;
}



