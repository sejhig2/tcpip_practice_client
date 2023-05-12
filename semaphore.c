/*
 * semaphore.c
 *
 *  Created on: 2023. 5. 12.
 *      Author: jhhwang
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t bin_sem = { 0 };
int number = 0;

void* thread_send(void *arg);
void* thread_recv(void *arg);

const char th1_text[] = "thread A :"; /* char * 로 선언하면 왜 안 되는걸까? char *text 와 char text[] 의 차이가 뭐지? */
const char th2_text[] = "thread B :";
const char th3_text[] = "thread C :";
const char th4_text[] = "thread D :";

int main(int argc, char **argv)
{
	int state = 0;
	void *thread_result = NULL;

	pthread_t th1 = 0;
	pthread_t th2 = 0;
	pthread_t th3 = 0;
	pthread_t th4 = 0;

	state = sem_init(&bin_sem, 0, 0);
	if (state != 0) {
		printf("fail to initialize semaphore\n");
		exit(1);
	}

	pthread_create(&th1, NULL, thread_send, &th1_text);
	pthread_create(&th2, NULL, thread_recv, &th2_text);
	pthread_create(&th3, NULL, thread_recv, &th3_text);
	pthread_create(&th4, NULL, thread_recv, &th4_text);

	pthread_join(th1, &thread_result);
	pthread_join(th2, &thread_result);
	pthread_join(th3, &thread_result);
	pthread_join(th4, &thread_result);

	printf("최종 데이터 : %d ", number);
	sem_destroy(&bin_sem);

	return 0;
}

void* thread_send(void *arg)
{
	int i = 0;
	for (i = 0; i < 9; i++) {
		while(number != 0) {
			sleep(1);
		}
		number++;
		printf("%s 최신 데이터를 기록합니다 \n", (char*) arg);
		sem_post(&bin_sem);
	}
}

void* thread_recv(void *arg)
{
	int i = 0;
	for (i = 0; i < 3; i++) {
		sem_wait(&bin_sem);
		number--;
		printf("%s 최신 데이터를 가져옵니다 \n", (char*) arg);

	}
}
