/*
 * writev.c
 *
 *  Created on: 2023. 5. 11.
 *      Author: jhhwang
 */

#include <stdio.h>
#include <sys/uio.h>

int main(int argc, char **argv)
{
	struct iovec vec[2] = { 0 };
	char msg1[] = "computer! ";
	char msg2[] = "communication!";
	int str_len = 0;

	vec[0].iov_base = msg1;
	vec[1].iov_base = msg2;

	vec[0].iov_len = sizeof(msg1);
	vec[1].iov_len = sizeof(msg2);

	str_len = writev(1, vec, 2);
	/* msg1과 msg2가 모두 출력돼야하는데 왜 하나만 출력되는거지? */
	/* msg1의 끝에 널을 포함하기 때문에 stdout할 때 msg1의 널까지만 출력됐다.*/
	printf("\n총 %d 바이트 출력 \n", str_len);

	return 0;
}
