/*
 * handle_stream.c
 *
 *  Created on: 2023. 5. 11.
 *      Author: jhhwang
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "error_handling.h"

int main(int argc, char **argv)
{
	int fildes = 0;
	FILE *fp = NULL;

	/* (리눅스) 시스템 함수를 이용해서 파일 디스크립터 생성 */
	fildes = open("data.dat", O_WRONLY | O_CREAT | O_TRUNC);
	//fildes = open("/usr/local/JH/project_in_eclipse/tcp_ip_socket_programing_client/src/data.dat",O_WRONLY | O_CREAT | O_TRUNC);
	if (fildes == -1) {
		error_handling("file open error");
		/* 에러 발생. open()함수에서 상대 경로를 넣어주면 왜 안 될까? */
	}

	/* 파일 디스크립터를 이용해서 파일 포인터 생성 */
	fp = fdopen(fildes, "w");

	fputs("network c programming \n\n", fp);
	fclose(fp);
	return 0;
}
