/*
 * news_receiver.c
 *
 *  Created on: 2023. 5. 10.
 *      Author: jhhwang
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>

#include "error_handling.h"

#define BUFSIZE (30)

int main(int argc, char **argv)
{
	int recv_sock = 0;
	struct sockaddr_in addr = { 0 };
	int state = 0;
	int str_len = 0;
	char buf[BUFSIZE] = { 0 };
	struct ip_mreq join_addr = { 0 };

	if (argc != 3) {
		printf("Usage : %s <GroupIP> <port> \n", argv[0]);
		exit(1);
	}
	recv_sock = socket(PF_INET, SOCK_DGRAM, 0); /* 멀티 캐스트를 위한 UDP 소캣 생성 */
	if (recv_sock == -1) {
		error_handling("socket() error");
	}

	memset(&addr, 0, sizeof(addr));
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(argv[2])); /* 멀티 캐스트 포트 설정 */

	if (bind(recv_sock, (struct sockaddr*) &addr, sizeof(addr)) == -1) {
		error_handling("bind() error");
	}

	join_addr.imr_multiaddr.s_addr = inet_addr(argv[1]);
	join_addr.imr_interface.s_addr = htonl(INADDR_ANY);

	state = setsockopt(recv_sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void*) &join_addr,
	            sizeof(join_addr));
	if (state) {
		error_handling("setsockopt() error");
	}

	while(1) {
		str_len = recvfrom(recv_sock, buf, BUFSIZE - 1, 0, NULL, 0);
		if (str_len < 0) {
			break;
		}
		buf[str_len] = 0;
		fputs(buf, stdout);
	}
	close(recv_sock);

	return 0;
}
