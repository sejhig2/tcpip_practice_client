/*
 * thread3.c
 *
 *  Created on: 2023. 5. 12.
 *      Author: jhhwang
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void* thread_function(void *arg);
/* 스레드에 전달할 파라미터. void pointer로 던져서 char* 로 캐스팅해서 사용할 예정*/
char thread1[] = "A Thread";
char thread2[] = "B Thread";

pthread_mutex_t mutx; // mutex lock, unlock 하기 위해 mutex 선언.
int number = 0; // critical section으로 여러 thread가 사용.

int main(int argc, char **argv)
{
	void *thread_result = NULL;
	pthread_t t1 = 0;
	pthread_t t2 = 0;
	int state = 0;

	state = pthread_mutex_init(&mutx, NULL);
	if (state) {
		puts("뮤텍스 초기화 실패 \n");
		exit(1);
	}

	pthread_create(&t1, NULL, thread_function, &thread1);
	pthread_create(&t2, NULL, thread_function, &thread2);

	pthread_join(t1, &thread_result);
	pthread_join(t2, &thread_result);

	printf("최종 number : %d \n", number);
	pthread_mutex_destroy(&mutx);

	return 0;
}

void* thread_function(void *arg)
{
	int i = 0;
	for (i = 0; i < 5; i++) {
		pthread_mutex_lock(&mutx);
		sleep(1);
		number++;
		printf("%s %d\n", (char*) arg, number);
		pthread_mutex_unlock(&mutx);
	}
}
