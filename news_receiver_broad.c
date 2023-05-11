/*
 * news_receiver_broad.c
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

#include  "error_handling.h"

#define BUFSIZE (30)

int main(int argc, char **argv)
{
	int recv_sock = 0; /* receive socket 의 파일 디스크립터 */
	struct sockaddr_in addr = { 0 };
	int str_len = 0;
	char buf[BUFSIZE] = { 0 };

	if (argc != 2) {
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}

	recv_sock = socket(PF_INET, SOCK_DGRAM, 0);
	if (recv_sock == -1) {
		error_handling("socket() error");
	}

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(atoi(argv[1]));

	if (bind(recv_sock, (struct sockaddr*) &addr, sizeof(addr)) == -1) {
		error_handling("bind() error");
	}

	while(1) {
		str_len = recvfrom(recv_sock, buf, BUFSIZE - 1, 0, NULL, 0);
		if (str_len) {
			break;
		}
		buf[str_len] = 0;
		fputs(buf, stdout);
	}
	close(recv_sock);

	return 0;
}
