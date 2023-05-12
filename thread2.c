/*
 * thread2.c
 *
 *  Created on: 2023. 5. 12.
 *      Author: jhhwang
 */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

void* thread_function(void *argv);

int main(int argc, char **argv)
{

	int state = 0;
	pthread_t t_id = 0;
	void *t_return = NULL;

	/* 스레드 생성. 옵션과 thread_function의 파라미터는 NULL */
	state = pthread_create(&t_id, NULL, thread_function, NULL);
	if (state != 0) {
		puts("스레드 생성 오류");
		exit(1);
	}
	printf("생성된 스레드 ID : %d \n", t_id);

	/* 스레도 종료시까지 main 함수의 실행을 지연시킴 */
	state = pthread_join(t_id, &t_return);
	if (state != 0) {
		puts("스레드 join 오류 ");
		exit(1);
	}

	printf("main함수 종료, 스레드 리턴 : %s \n", (char*) t_return);
	free(t_return);

	return 0;
}

void* thread_function(void *arg)
{
	int i = 0;
	/* 메모리를 동적할당해서 string을 입력 -> 반한값으로 string의 포인터 */
	char *p = (char*) calloc(20, sizeof(char));
	strcpy(p, "스레드 종료됨\n");

	for (i = 0; i < 3; i++) {
		sleep(2);
		puts("스레드 실행 중");
	}

	return p;
}

