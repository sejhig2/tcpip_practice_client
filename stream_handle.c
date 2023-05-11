/*
 * stream_handle.c
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

int main(void)
{
	int fildes = 0;
	FILE *fp = NULL;
	/* 파일 디스크립터 생성 */
	fildes = open("./data.dat", O_WRONLY | O_CREAT | O_TRUNC); //절대 경로가 아니면 왜 에러가 발생할까?
	if (fildes == -1) {
		error_handling("file open error");
	}

	printf("First file descripter : %d \n", fildes);
	/* 파일 디스크립터 -> 파일 포인터 */
	fp = fdopen(fildes, "w");
	fputs("TCP/IP Socekt Programming \n\n", fp);

	/*파일 포인터로 파일 디스크립터 생성 후 화면 출력 */
	printf("second file descripter : %d \n\n", fileno(fp));

	return 0;
}
